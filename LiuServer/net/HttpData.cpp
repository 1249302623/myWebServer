#include"HttpData.h"
#include<iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include"ConnChannel.h"
#include"SqlConnPool.h"
#include"Singleton.h"
#include"EventLoop.h"
pthread_once_t MimeType::once_control = PTHREAD_ONCE_INIT;
std::unordered_map<std::string, std::string> MimeType::mime;
char favicon[555] = {
    '\x89', 'P',    'N',    'G',    '\xD',  '\xA',  '\x1A', '\xA',  '\x0',
    '\x0',  '\x0',  '\xD',  'I',    'H',    'D',    'R',    '\x0',  '\x0',
    '\x0',  '\x10', '\x0',  '\x0',  '\x0',  '\x10', '\x8',  '\x6',  '\x0',
    '\x0',  '\x0',  '\x1F', '\xF3', '\xFF', 'a',    '\x0',  '\x0',  '\x0',
    '\x19', 't',    'E',    'X',    't',    'S',    'o',    'f',    't',
    'w',    'a',    'r',    'e',    '\x0',  'A',    'd',    'o',    'b',
    'e',    '\x20', 'I',    'm',    'a',    'g',    'e',    'R',    'e',
    'a',    'd',    'y',    'q',    '\xC9', 'e',    '\x3C', '\x0',  '\x0',
    '\x1',  '\xCD', 'I',    'D',    'A',    'T',    'x',    '\xDA', '\x94',
    '\x93', '9',    'H',    '\x3',  'A',    '\x14', '\x86', '\xFF', '\x5D',
    'b',    '\xA7', '\x4',  'R',    '\xC4', 'm',    '\x22', '\x1E', '\xA0',
    'F',    '\x24', '\x8',  '\x16', '\x16', 'v',    '\xA',  '6',    '\xBA',
    'J',    '\x9A', '\x80', '\x8',  'A',    '\xB4', 'q',    '\x85', 'X',
    '\x89', 'G',    '\xB0', 'I',    '\xA9', 'Q',    '\x24', '\xCD', '\xA6',
    '\x8',  '\xA4', 'H',    'c',    '\x91', 'B',    '\xB',  '\xAF', 'V',
    '\xC1', 'F',    '\xB4', '\x15', '\xCF', '\x22', 'X',    '\x98', '\xB',
    'T',    'H',    '\x8A', 'd',    '\x93', '\x8D', '\xFB', 'F',    'g',
    '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f',    'v',    'f',    '\xDF',
    '\x7C', '\xEF', '\xE7', 'g',    'F',    '\xA8', '\xD5', 'j',    'H',
    '\x24', '\x12', '\x2A', '\x0',  '\x5',  '\xBF', 'G',    '\xD4', '\xEF',
    '\xF7', '\x2F', '6',    '\xEC', '\x12', '\x20', '\x1E', '\x8F', '\xD7',
    '\xAA', '\xD5', '\xEA', '\xAF', 'I',    '5',    'F',    '\xAA', 'T',
    '\x5F', '\x9F', '\x22', 'A',    '\x2A', '\x95', '\xA',  '\x83', '\xE5',
    'r',    '9',    'd',    '\xB3', 'Y',    '\x96', '\x99', 'L',    '\x6',
    '\xE9', 't',    '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',    '\xA7',
    '\xC4', 'b',    '1',    '\xB5', '\x5E', '\x0',  '\x3',  'h',    '\x9A',
    '\xC6', '\x16', '\x82', '\x20', 'X',    'R',    '\x14', 'E',    '6',
    'S',    '\x94', '\xCB', 'e',    'x',    '\xBD', '\x5E', '\xAA', 'U',
    'T',    '\x23', 'L',    '\xC0', '\xE0', '\xE2', '\xC1', '\x8F', '\x0',
    '\x9E', '\xBC', '\x9',  'A',    '\x7C', '\x3E', '\x1F', '\x83', 'D',
    '\x22', '\x11', '\xD5', 'T',    '\x40', '\x3F', '8',    '\x80', 'w',
    '\xE5', '3',    '\x7',  '\xB8', '\x5C', '\x2E', 'H',    '\x92', '\x4',
    '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g',    '\x98', '\xE9',
    '6',    '\x1A', '\xA6', 'g',    '\x15', '\x4',  '\xE3', '\xD7', '\xC8',
    '\xBD', '\x15', '\xE1', 'i',    '\xB7', 'C',    '\xAB', '\xEA', 'x',
    '\x2F', 'j',    'X',    '\x92', '\xBB', '\x18', '\x20', '\x9F', '\xCF',
    '3',    '\xC3', '\xB8', '\xE9', 'N',    '\xA7', '\xD3', 'l',    'J',
    '\x0',  'i',    '6',    '\x7C', '\x8E', '\xE1', '\xFE', 'V',    '\x84',
    '\xE7', '\x3C', '\x9F', 'r',    '\x2B', '\x3A', 'B',    '\x7B', '7',
    'f',    'w',    '\xAE', '\x8E', '\xE',  '\xF3', '\xBD', 'R',    '\xA9',
    'd',    '\x2',  'B',    '\xAF', '\x85', '2',    'f',    'F',    '\xBA',
    '\xC',  '\xD9', '\x9F', '\x1D', '\x9A', 'l',    '\x22', '\xE6', '\xC7',
    '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15', '\x90', '\x7',  '\x93',
    '\xA2', '\x28', '\xA0', 'S',    'j',    '\xB1', '\xB8', '\xDF', '\x29',
    '5',    'C',    '\xE',  '\x3F', 'X',    '\xFC', '\x98', '\xDA', 'y',
    'j',    'P',    '\x40', '\x0',  '\x87', '\xAE', '\x1B', '\x17', 'B',
    '\xB4', '\x3A', '\x3F', '\xBE', 'y',    '\xC7', '\xA',  '\x26', '\xB6',
    '\xEE', '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
    '\xA',  '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X',    '\x0',  '\x27',
    '\xEB', 'n',    'V',    'p',    '\xBC', '\xD6', '\xCB', '\xD6', 'G',
    '\xAB', '\x3D', 'l',    '\x7D', '\xB8', '\xD2', '\xDD', '\xA0', '\x60',
    '\x83', '\xBA', '\xEF', '\x5F', '\xA4', '\xEA', '\xCC', '\x2',  'N',
    '\xAE', '\x5E', 'p',    '\x1A', '\xEC', '\xB3', '\x40', '9',    '\xAC',
    '\xFE', '\xF2', '\x91', '\x89', 'g',    '\x91', '\x85', '\x21', '\xA8',
    '\x87', '\xB7', 'X',    '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N',
    'N',    'b',    't',    '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
    '\xEC', '\x86', '\x2',  'H',    '\x26', '\x93', '\xD0', 'u',    '\x1D',
    '\x7F', '\x9',  '2',    '\x95', '\xBF', '\x1F', '\xDB', '\xD7', 'c',
    '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF', '\x22', 'J',    '\xC3',
    '\x87', '\x0',  '\x3',  '\x0',  'K',    '\xBB', '\xF8', '\xD6', '\x2A',
    'v',    '\x98', 'I',    '\x0',  '\x0',  '\x0',  '\x0',  'I',    'E',
    'N',    'D',    '\xAE', 'B',    '\x60', '\x82',
};
std::string PostRequest[]={
    "register.html",//0
    "log.html",//1
    "2",//2
    "3",//3
    "",//4
    "picture.html",//5
    "video.html"//6
};
void MimeType::init() {
  mime[".html"] = "text/html";
  mime[".avi"] = "video/x-msvideo";
  mime[".bmp"] = "image/bmp";
  mime[".c"] = "text/plain";
  mime[".doc"] = "application/msword";
  mime[".gif"] = "image/gif";
  mime[".gz"] = "application/x-gzip";
  mime[".htm"] = "text/html";
  mime[".ico"] = "image/x-icon";
  mime[".jpg"] = "image/jpeg";
  mime[".png"] = "image/png";
  mime[".txt"] = "text/plain";
  mime[".mp3"] = "audio/mp3";
  mime["default"] = "text/html";
}

std::string MimeType::getMime(const std::string &suffix) {
  pthread_once(&once_control, MimeType::init);
  if (mime.find(suffix) == mime.end())
    return mime["default"];
  else
    return mime[suffix];
}

HttpData::HttpData(ConnChannel* connPtr):
    error_(false),
    //connectionState_(H_CONNECTED),
    method_(METHOD_GET),
    HTTPVersion_(HTTP_11),
    nowReadPos_(0),
    state_(STATE_PARSE_URI),
    hState_(H_START),
    connChannel_(connPtr)
{
}
void HttpData::reset() {
  fileName_.clear();
  path_.clear();
  nowReadPos_ = 0;
  state_ = STATE_PARSE_URI;
  hState_ = H_START;
  headers_.clear();
  //connChannel_->reset();
}
URIState HttpData::parseURI() {
  std::string &str = httpinBuffer;
  std::string cop = str;
  // 读到完整的请求行再开始解析请求
  size_t pos = str.find('\r', nowReadPos_);
    //find(str,position),  find()的两个参数：
    // str：是要找的元素
    // position：字符串中的某个位置，表示从从这个位置开始的字符串中找指定元素。
    // 可以不填第二个参数，默认从字符串的开头进行查找。
  if (pos < 0) {
    return PARSE_URI_AGAIN;
  }
  // 去掉请求行所占的空间，节省空间
  std::string request_line = str.substr(0, pos);
  if (str.size() > pos + 1)
    str = str.substr(pos + 1);
  else
    str.clear();    //刚好截取到\r
  // Method
  int posGet = request_line.find("GET");
  int posPost = request_line.find("POST");
  int posHead = request_line.find("HEAD");

  if (posGet >= 0) {
    pos = posGet;
    method_ = METHOD_GET;
  } else if (posPost >= 0) {
    pos = posPost;
    method_ = METHOD_POST;
  } else if (posHead >= 0) {
    pos = posHead;
    method_ = METHOD_HEAD;
  } else {
    return PARSE_URI_ERROR;
  }

  // filename
  pos = request_line.find("/", pos);
  if (pos < 0) {
    fileName_ = "judge.html";
    HTTPVersion_ = HTTP_11;
    return PARSE_URI_SUCCESS;
  } else {
    size_t _pos = request_line.find(' ', pos);
    if (_pos < 0)
      return PARSE_URI_ERROR;
    else {
      if (_pos - pos > 1) {
        fileName_ = request_line.substr(pos + 1, _pos - pos - 1);
        size_t __pos = fileName_.find('?');
        if (__pos >= 0) {
          fileName_ = fileName_.substr(0, __pos);
        }
      }
      else
        fileName_ = "judge.html";
    }
    pos = _pos;
  }
  //std::cout << "fileName_: " << fileName_ << std::endl;
  // HTTP 版本号
  pos = request_line.find("/", pos);
  if (pos < 0)
    return PARSE_URI_ERROR;
  else {
    if (request_line.size() - pos <= 3)
      return PARSE_URI_ERROR;
    else {
      std::string ver = request_line.substr(pos + 1, 3);
      if (ver == "1.0")
        HTTPVersion_ = HTTP_10;
      else if (ver == "1.1")
        HTTPVersion_ = HTTP_11;
      else
        return PARSE_URI_ERROR;
    }
  }
  return PARSE_URI_SUCCESS;
}
HeaderState HttpData::parseHeaders() {
  std::string &str = httpinBuffer;
  int key_start = -1, key_end = -1, value_start = -1, value_end = -1;
  int now_read_line_begin = 0;
  bool notFinish = true;
  size_t i = 0;
  for (; i < str.size() && notFinish; ++i) {
    switch (hState_) {
      case H_START: {
        if (str[i] == '\n' || str[i] == '\r') 
            break;
        hState_ = H_KEY;
        key_start = i;
        now_read_line_begin = i;
        break;
      }
      case H_KEY: {
        if (str[i] == ':') {
          key_end = i;
          if (key_end - key_start <= 0) 
            return PARSE_HEADER_ERROR;
          hState_ = H_COLON;
        } 
        else if (str[i] == '\n' || str[i] == '\r')
          return PARSE_HEADER_ERROR;
        break;
      }
      case H_COLON: {
        if (str[i] == ' ') {
          hState_ = H_SPACES_AFTER_COLON;
        } 
        else
          return PARSE_HEADER_ERROR;
        break;
      }
      case H_SPACES_AFTER_COLON: {
        hState_ = H_VALUE;
        value_start = i;
        break;
      }
      case H_VALUE: {
        if (str[i] == '\r') {
          hState_ = H_CR;
          value_end = i;
          if (value_end - value_start <= 0) 
            return PARSE_HEADER_ERROR;
        } 
        else if (i - value_start > 255)
          return PARSE_HEADER_ERROR;
        break;
      }
      case H_CR: {
        if (str[i] == '\n') {
          hState_ = H_LF;
          std::string key(str.begin() + key_start, str.begin() + key_end);
          std::string value(str.begin() + value_start, str.begin() + value_end);
          headers_[key] = value;
          now_read_line_begin = i;
        } 
        else
          return PARSE_HEADER_ERROR;
        break;
      }
      case H_LF: {
        if (str[i] == '\r') {
          hState_ = H_END_CR;
        } 
        else {
          key_start = i;
          hState_ = H_KEY;
        }
        break;
      }
      case H_END_CR: {
        if (str[i] == '\n') {
          hState_ = H_END_LF;
        } 
        else
          return PARSE_HEADER_ERROR;
        break;
      }
      case H_END_LF: {
        notFinish = false;
        key_start = i;
        now_read_line_begin = i;
        break;
      }
    }
  }
  if (hState_ == H_END_LF) {
    str = str.substr(i);
    return PARSE_HEADER_SUCCESS;
  }
  str = str.substr(now_read_line_begin);//提取从0到now_read_line_begin的字符串
  return PARSE_HEADER_AGAIN;
}
AnalysisState HttpData::analysisRequest() {
  std::string header;
  if (method_ == METHOD_POST) {
    //std::string header;
    header += std::string("HTTP/1.1 200 OK\r\n");
    if(headers_.find("Connection") != headers_.end() &&
        headers_["Connection"] == "Keep-Alive")
    {
        this->connChannel_->setkeepAlive(true);
        header += std::string("Connection: Keep-Alive\r\n") + "Keep-Alive: timeout=" + 
          std::to_string(DEFAULT_KEEP_ALIVE_TIME) + "\r\n";
    }

  } 
  else if (method_ == METHOD_GET || method_ == METHOD_HEAD) {
    //std::string header;
    header += "HTTP/1.1 200 OK\r\n";
    if (headers_.find("Connection") != headers_.end() &&
        (headers_["Connection"] == "Keep-Alive" ||headers_["Connection"] == "keep-alive")) 
    {
      this->connChannel_->setkeepAlive(true);
      header += std::string("Connection: Keep-Alive\r\n") + "Keep-Alive: timeout=" +
                std::to_string(DEFAULT_KEEP_ALIVE_TIME) + "\r\n";
    }
  }
  if (method_ == METHOD_POST||method_ == METHOD_GET || method_ == METHOD_HEAD)
  {
    if(method_ == METHOD_POST){
      //assert(fileName_.size()==1);
      int num=fileName_[0]-'0';
      if(num<0||num>6){
        httpoutBuffer.clear();
        handleError(404, "错误的地址");
        return ANALYSIS_ERROR;
      }
      fileName_=PostRequest[num];
      if(fileName_=="2"){
          bool dealdb=dealDBlog(headers_["BODY"]);
          if(dealdb)
            fileName_="welcome.html";
          else
            fileName_="logError.html";
      }
      else if(fileName_=="3"){
          bool bo=dealDBreg(headers_["BODY"]);
          if(bo)
            fileName_="log.html";
          else
            fileName_="registerError.html";
      }
    }
    int dot_pos = fileName_.find('.');
    if(headers_.find("Referer")== headers_.end()&&fileName_!="judge.html"
          &&fileName_!="favicon.ico"&&fileName_!="fans.html"&&fileName_!="log.html"){
        httpoutBuffer.clear();
        handleError(404, "错误的地址");
        return ANALYSIS_ERROR;
    }
    std::string filetype;
    if (dot_pos < 0)
      filetype = MimeType::getMime("default");
    else
      filetype = MimeType::getMime(fileName_.substr(dot_pos));

    if (fileName_ == "favicon.ico") {
      header += "Content-Type: image/png\r\n";
      header += "Content-Length: " + std::to_string(sizeof favicon) + "\r\n";
      header += "Server: Liu's Web Server\r\n";

      header += "\r\n";
      httpoutBuffer += header;
      httpoutBuffer+= std::string(favicon, favicon + sizeof favicon);
      return ANALYSIS_SUCCESS;
    }

    fileName_="html/"+fileName_;
    struct stat sbuf;
    if (stat(fileName_.c_str(), &sbuf) < 0) {
      header.clear();
      handleError(404, "Not Found!");
      return ANALYSIS_ERROR;
    }
    header += "Content-Type: " + filetype + "\r\n";
    header += "Content-Length: " + std::to_string(sbuf.st_size) + "\r\n";
    header += "Server: liu's Web Server\r\n";
    // 头部结束
    header += "\r\n";
    httpoutBuffer += header;

    if (method_ == METHOD_HEAD) return ANALYSIS_SUCCESS;

    int src_fd = open(fileName_.c_str(), O_RDONLY, 0);
    if (src_fd < 0) {
      httpoutBuffer.clear();
      handleError(404, "Not Found!");
      return ANALYSIS_ERROR;
    }
    void *mmapRet = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    //系统自动选择存取地址，文件中全部都映射到内存，映射区域可被读取，对此区域作的任何修改都不会写回原来的文件内容。要映射到内存中的文件描述符src_fd
    close(src_fd);
    if (mmapRet == (void *)-1) {  //映射失败
      munmap(mmapRet, sbuf.st_size); //取消映射
      httpoutBuffer.clear();
      handleError(404, "Not Found!");
      return ANALYSIS_ERROR;
    }
    char *src_addr = static_cast<char *>(mmapRet);
    httpoutBuffer+= std::string(src_addr, src_addr + sbuf.st_size);
    munmap(mmapRet, sbuf.st_size);
    return ANALYSIS_SUCCESS;
  }

  return ANALYSIS_ERROR;
}
//void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize); 
//参数start：指向欲映射的内存起始地址，通常设为 NULL，代表让系统自动选定地址，映射成功后返回该地址。
// 参数length：代表将文件中多大的部分映射到内存。
// 参数prot：映射区域的保护方式。可以为以下几种方式的组合：
// PROT_EXEC 映射区域可被执行
// PROT_READ 映射区域可被读取
// PROT_WRITE 映射区域可被写入
// PROT_NONE 映射区域不能存取
// 参数flags：影响映射区域的各种特性。在调用mmap()时必须要指定MAP_SHARED 或MAP_PRIVATE。
// MAP_FIXED 如果参数start所指的地址无法成功建立映射时，则放弃映射，不对地址做修正。通常不鼓励用此旗标。
// MAP_SHARED对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享。
// MAP_PRIVATE 对映射区域的写入操作会产生一个映射文件的复制，即私人的“写入时复制”（copy on write）对此区域作的任何修改都不会写回原来的文件内容。
// MAP_ANONYMOUS建立匿名映射。此时会忽略参数fd，不涉及文件，而且映射区域无法和其他进程共享。
// MAP_DENYWRITE只允许对映射区域的写入操作，其他对文件直接写入的操作将会被拒绝。
// MAP_LOCKED 将映射区域锁定住，这表示该区域不会被置换（swap）。
// 参数fd：要映射到内存中的文件描述符。如果使用匿名内存映射时，即flags中设置了MAP_ANONYMOUS，fd设为-1。有些系统不支持匿名内存映射，则可以使用fopen打开/dev/zero文件，然后对该文件进行映射，可以同样达到匿名内存映射的效果。
// 参数offset：文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。
void HttpData::handleError(int err_num, std::string short_msg) {
  short_msg = " " + short_msg;
  char send_buff[4096];
  std::string body_buff, header_buff;
  body_buff += "<html><meta charset=\"UTF-8\"> <title>哎~出错了</title>";
  body_buff += "<body bgcolor=\"ffffff\">";
  body_buff += std::to_string(err_num) + short_msg;
  body_buff += "<hr><em> Hello World 错误</em>\n<br/><br/><br/>";
  body_buff+="<a href=\"http://139.9.78.161:8080/\">从此处进入</a>";
  body_buff+="</body></html>";

  header_buff += "HTTP/1.1 " + std::to_string(err_num) + short_msg + "\r\n";
  header_buff += "Content-Type: text/html\r\n";
  header_buff += "Connection: Close\r\n";
  header_buff += "Content-Length: " + std::to_string(body_buff.size()) + "\r\n";
  header_buff += "Server: Liu's Server\r\n";
  ;
  header_buff += "\r\n";
  // 错误处理不考虑writen不完的情况
  httpoutBuffer=header_buff+body_buff;
}
void HttpData::dealHttpData(){
  {
    MutexLockGuard lock(connChannel_->getinputBufferMutex());
    this->httpinBuffer=connChannel_->getinputBuffer().retrieveAllAsString();
  }
  //_INFO<<"work recive ip=:"<<connChannel_->getPeerAddress()<<"  size="<<httpinBuffer;
  do{
    if (state_ == STATE_PARSE_URI) {
      URIState flag = this->parseURI();
      if (flag == PARSE_URI_AGAIN){
        break;
      }
      else if (flag == PARSE_URI_ERROR) {
        //perror("2");
        //LOG_INFO<< "PARSE_URI_ERROR ip = " << this->connChannel_->getPeerAddress()<< ",";
        httpinBuffer.clear();
        error_ = true;
        handleError(400, "Bad Request");
        break;
      } 
      else
        state_ = STATE_PARSE_HEADERS;
    }
    if (state_ == STATE_PARSE_HEADERS) {
      HeaderState flag = this->parseHeaders();
      
      if (flag == PARSE_HEADER_AGAIN)
        break;
      else if (flag == PARSE_HEADER_ERROR) {
        perror("3");
        error_ = true;
        //LOG_INFO<< "HEAD_ERROR ip = " << this->connChannel_->getPeerAddress();
        handleError(400, "Bad Request");
        break;
      }
      if (method_ == METHOD_POST) {
        // POST方法准备
        state_ = STATE_RECV_BODY;
        
      } 
      else {
        state_ = STATE_ANALYSIS;
      }
    }
    if (state_ == STATE_RECV_BODY) {
      
      int content_length = -1;
      if (headers_.find("Content-Length") != headers_.end()) {
        content_length = stoi(headers_["Content-Length"]);
        
      } 
      else {
        error_ = true;
        handleError(400, "Bad Request: Lack of argument (Content-Length)");
        break;
      }
      if (static_cast<int>(httpinBuffer.size()+1) < content_length){
        break;
      }
      headers_["BODY"]=httpinBuffer;
      //std::cout<<headers_["BODY"]<<std::endl;
      state_ = STATE_ANALYSIS;
    }
    if (state_ == STATE_ANALYSIS) {
      AnalysisState flag = this->analysisRequest();
      if (flag == ANALYSIS_SUCCESS) {
        state_ = STATE_FINISH;
        break;
      } 
      else {
        // cout << "state_ == STATE_ANALYSIS" << endl;
        error_ = true;
        break;
      }
    }
  }while (false);
  if (httpoutBuffer.size() > 0){
    {
    MutexLockGuard lock(connChannel_->getoutputBufferMutex());
    connChannel_->getoutputBuffer().append(httpoutBuffer);
    }
    //LOG_INFO<<"outputsize="<<httpoutBuffer.size();
    httpoutBuffer.clear();
    connChannel_->getEvents() |= EPOLLOUT;//要发送
    connChannel_->seperateTimer();
    int timeout=DEFAULT_EXPIRED_TIME;
    connChannel_->getloop()->runInLoop(std::bind(&EventLoop::updatePoller,
      connChannel_->getloop(),connChannel_,timeout));
    //connChannel_->getloop()->updatePoller(connChannel_,0);
  }  
  if (state_ == STATE_FINISH) {
    this->reset();  
  }
}
bool dealDBlog(std::string body){
  std::string user,password;
  get_user_and_pwd(body,user,password);
  SqlConnRAII sqlconn(&Singleton<SqlConnPool>::instance());
  bool bo=sqlconn.sqlQuery("SELECT * FROM loginfo where name='"+user+"' and password='"+password+"';");
  return bo;
  //std::cout<<"user="<<user<<"pwd="<<password<<std::endl;
}
bool dealDBreg(std::string body){
  std::string user,password;
  get_user_and_pwd(body,user,password);
  SqlConnRAII sqlconn(&Singleton<SqlConnPool>::instance());
  bool bo=sqlconn.sqlQuery("SELECT * FROM loginfo where name='"+user+"';");
  if(bo==true)//存在
    return false;
  else{
    bool bo1=sqlconn.sqlinsert(
      "insert into loginfo (name,password) values ('"+user+"','"+password+"');");
    return bo1;
  }
}
void get_user_and_pwd(std::string body,std::string& user,std::string& password){
  int i=0;
  while(i<body.size()&&body[i]!='=') i++;
  i++;
  while(i<body.size()&&body[i]!='&'){
    user+=body[i];
    i++;
  }
  while(i<body.size()&&body[i]!='=') i++;
  i++;
  while(i<body.size()){
    password+=body[i];
    i++;
  }
}