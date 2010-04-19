#ifndef __OPTION_H__
#define __OPTION_H__

#include <string>
#include <vector>

class Option {
  
 public :
  Option(std::string const &, std::string const &, std::string const &, std::string const &, bool, std::vector<std::string> const &);
  virtual ~Option();  
  void setName(std::string const &);
  void setCommutatorShort(std::string const &);
  void setCommutatorLong(std::string const &);
  void setOptargc(std::string const &);
  void setMandatory(bool);
  void setValue(std::vector<std::string> const &);
  std::string const & getName() const;
  std::string const & getCommutatorShort() const;
  std::string const & getCommutatorLong() const;
  std::string const & getOptargc() const ;
  bool getMandatory() const;
  std::vector<std::string> const & getValue() const;

 private:
  std::string _name;
  std::string _commutatorShort ;
  std::string _commutatorLong;
  std::string _optargc;
  bool _mandatory;
  std::vector<std::string> _values;
};

#endif
