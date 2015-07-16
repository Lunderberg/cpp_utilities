#ifndef _POPENSTREAM_H_
#define _POPENSTREAM_H_

#include <cstring>
#include <istream>
#include <streambuf>
#include <vector>

// TODO:
//    Implement PopenStreamBuf::seekoff
//    Implement PopenStreamBuf::seekpos
// Definitions from http://www.cplusplus.com/reference/streambuf/streambuf

class PopenStreamBuf : public std::streambuf {
public:
  PopenStreamBuf(const char* command, std::size_t buf_size = 256, std::size_t put_back = 8);
  ~PopenStreamBuf();

  void Close();

private:
  int underflow();
  std::streamsize xsgetn(char* s, std::streamsize n);
  std::streamsize showmanyc();

  PopenStreamBuf(const PopenStreamBuf&) = delete;
  PopenStreamBuf operator=(const PopenStreamBuf&) = delete;

private:
  FILE* p;
  const std::size_t put_back;
  std::vector<char> buffer;
};

class PopenStream : public std::istream {
public:
  PopenStream(const char* command)
    : std::ios(0), std::istream(&stream_buf), stream_buf(command) { }

  virtual ~PopenStream() { }

private:
  PopenStreamBuf stream_buf;
};

#endif /* _POPENSTREAM_H_ */
