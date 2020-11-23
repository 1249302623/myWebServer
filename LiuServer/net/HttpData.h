#pragma once
#include<string>
#include<map>
#include<unordered_map>
enum ProcessState {
  STATE_PARSE_URI = 1,
  STATE_PARSE_HEADERS,
  STATE_RECV_BODY,
  STATE_ANALYSIS,
  STATE_FINISH
};

enum URIState {
  PARSE_URI_AGAIN = 1,
  PARSE_URI_ERROR,
  PARSE_URI_SUCCESS,
};

enum HeaderState {
  PARSE_HEADER_SUCCESS = 1,
  PARSE_HEADER_AGAIN,
  PARSE_HEADER_ERROR
};
enum BodyState {
  PARSE_BODY_SUCCESS = 1,
  PARSE_BODY_AGAIN,
  PARSE_BODY_ERROR
};
enum AnalysisState { ANALYSIS_SUCCESS = 1, ANALYSIS_ERROR };

enum ParseState {
  H_START = 0,
  H_KEY,
  H_COLON,
  H_SPACES_AFTER_COLON,
  H_VALUE,
  H_CR,
  H_LF,
  H_END_CR,
  H_END_LF
};

enum HttpMethod { METHOD_POST = 1, METHOD_GET, METHOD_HEAD };
enum HttpVersion { HTTP_10 = 1, HTTP_11 };
bool dealDBreg(std::string body);
bool dealDBlog(std::string body);
void get_user_and_pwd(std::string body,std::string& user,std::string& password);
class ConnChannel;
class HttpData{
public:
    HttpData(ConnChannel* connPtr);
    ~HttpData(){}
    void reset();
    void dealHttpData();
private:
    bool error_;
    ConnChannel* connChannel_;
    //ConnectionState connectionState_;
    std::string httpinBuffer;
    std::string httpoutBuffer;
    HttpMethod method_;
    HttpVersion HTTPVersion_;
    std::string fileName_;
    std::string path_;
    int nowReadPos_;
    ProcessState state_;
    ParseState hState_;
    std::map<std::string, std::string> headers_;
    URIState parseURI();
    HeaderState parseHeaders();

    AnalysisState analysisRequest();
    void handleError(int err_num, std::string short_msg) ; 
};

class MimeType {
 private:
  static void init();
  static std::unordered_map<std::string, std::string> mime;
  MimeType();
  MimeType(const MimeType &m);

 public:
  static std::string getMime(const std::string &suffix);

 private:
  static pthread_once_t once_control;
};