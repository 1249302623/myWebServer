#include "FileUtil.h"
#include <stdio.h>
AppendFile::AppendFile(std::string filename):
	fp_(fopen(filename.c_str(),"ae"))//e :O_CLOEXEC 应该表示执行exec()时，之前通过open()打开的文件描述符会自动关闭
{
	setbuffer(fp_, buffer_, sizeof buffer_);
	//在打开文件流后，读取内容之前，调用setbuffer()可用来设置文件流的缓冲区。参数stream为指定的文件流，参数buf指向自定的缓冲区起始地址，参数size为缓冲区大小
}

AppendFile::~AppendFile(){
	fclose(fp_);
}

void AppendFile::append(const char* logline, const size_t len)//不是线程安全的，需要外部加锁
{
	size_t n = this->write(logline, len);//fwrite将数据写入写缓冲区，除非缓冲区已满，否则不写入文件。遇换行符或缓冲区满时，将刷新缓冲区；
	size_t remain = len - n;
	while (remain > 0) {
		size_t x = this->write(logline + n, remain);
		if (x == 0) {
			int err = ferror(fp_);
			if (err) fprintf(stderr, "AppendFile::append() failed !\n");
			break;
		}
		n += x;
		remain = len - n;
	}
}

void AppendFile::flush()
{
	fflush(fp_);//清除一个流，即清除文件缓冲区，当文件以写方式打开时，将缓冲区内容写入文件。
}

size_t AppendFile::write(const char* logline, size_t len)
{
	return fwrite_unlocked(logline, 1, len, fp_);//size 设置为1，代表一个字节一个字节的写入文件。
}
	//size_t fwrite(const void * ptr, size_t size, size_t nmemb, FILE * stream);
	//fwrite()用来将数据写入文件流中. 参数stream 为已打开的文件指针, 参数ptr 指向欲写入的数据地址,size是数据块的大小（字节数）
	//总共写入的字符数以参数size*nmemb 来决定. Fwrite()会返回实际写入的nmemb 数目
	//fwrite_unlocked（）与fwrite（）相同，只是它不需要是线程安全的,fwrite_unlocked()函数，以不加锁的方式写文件，不线程安全，但是效率高。
