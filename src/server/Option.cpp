#include "Option.h"

Option::Option(std::string const & name, std::string const & commutatorShort, std::string const & commutatorLong, std::string const & optargc, bool mandatory, std::vector<std::string> const & values)
  : _name(name), _commutatorShort(commutatorShort), _commutatorLong(commutatorLong), _optargc(optargc), _mandatory(mandatory), _values(values) {}

Option::~Option() {}

void Option::setName(std::string const & name) {
  _name = name;
}

std::string const & Option::getName() const {
  return _name;
}

void Option::setCommutatorShort(std::string const & commutatorShort) {
  _commutatorShort = commutatorShort;
}

std::string const & Option::getCommutatorShort() const {
  return _commutatorShort;
}

void Option::setCommutatorLong(std::string const & commutatorLong) {
  _commutatorLong = commutatorLong;
}

std::string const & Option::getCommutatorLong() const {
  return _commutatorLong;
}

void Option::setOptargc(std::string const & optargc) {
  _optargc = optargc;
}

std::string const & Option::getOptargc() const {
  return _optargc;
}

void Option::setMandatory(bool mandatory) {
  _mandatory = mandatory;
}

bool Option::getMandatory() const {
  return _mandatory;
}

void Option::setValue(std::vector<std::string> const & value) {
  _values = value;
}

std::vector<std::string> const & Option::getValue() const {
  return _values;
}
