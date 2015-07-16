#include "PopenStream.hh"

#include <iostream>


PopenStreamBuf::PopenStreamBuf(const char* command, std::size_t buf_size, std::size_t put_back)
  : p(NULL),
    put_back(std::max(put_back, size_t(1))),
    buffer(std::max(buf_size, put_back) + put_back) {
  p = popen(command, "r");
  char* end = buffer.data() + buffer.size();
  setg(end,end,end);
}

PopenStreamBuf::~PopenStreamBuf(){
  Close();
}

void PopenStreamBuf::Close(){
  if(p != NULL){
    pclose(p);
    p = NULL;
  }
}


// eback(), the start of the buffer
// gptr(), the "get" pointer
// egptr(), one past the end of the valid region
int PopenStreamBuf::underflow(){
  if(gptr() < egptr()){
    return traits_type::to_int_type(*gptr());
  }

  char* base = buffer.data();
  char* start = base;

  if(eback() == base){
    std::memmove(base, egptr() - put_back, put_back);
    start += put_back;
  }

  size_t chars_read = fread(start, sizeof(char), buffer.size() - (start-base), p);
  if(chars_read==0){
    return traits_type::eof();
  }

  setg(base, start, start + chars_read);

  return traits_type::to_int_type(*gptr());
}

std::streamsize PopenStreamBuf::xsgetn(char* s, std::streamsize requested){
  std::streamsize cached = showmanyc();
  if(requested <= cached){
    memcpy(s, gptr(), requested*sizeof(char));
    gbump(requested);
    return requested;
  }
  memcpy(s, gptr(), cached*sizeof(char));
  gbump(cached);

  if(underflow() == traits_type::eof()){
    return cached;
  }

  return (cached + xsgetn(s+cached, requested-cached));
}

std::streamsize PopenStreamBuf::showmanyc(){
  return egptr() - gptr();
}
