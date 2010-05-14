#ifndef __OPTION_H__
#define __OPTION_H__

#include <string>
#include <vector>

//! CLIENT: Handle list of server options.

class Option 
{ 
 public :

  Option(std::string const &, std::string const &, std::string const &, std::string const &, bool, std::vector<std::string> const &);
  virtual ~Option();

  //! Set Name of option.
  /*! \param 1 name of option */
  void				setName(std::string const &);
  //! Set command line commutator short of option.
  /*! \param 1 name of short commutator */
  void				setCommutatorShort(std::string const &);
  //! Set command line commutator long of option.
  /*! \param 1 name of long commutator */
  void				setCommutatorLong(std::string const &);
  //! Set optargc.
  /*! \param 1 optargc */
  void				setOptargc(std::string const &);
  //! Set if option is mandatory.
  /*! \param 1 bool is mandatory */
  void				setMandatory(bool);
  //! Set value of option.
  /*! \param 1 string value of option */
  void				setValue(std::vector<std::string> const &);

  //! Get name of option.
  /*! \return string name of option */
  std::string const &		getName() const;
  //! Get commutator short.
  /*! \return string commutator short */
  std::string const &		getCommutatorShort() const;
  //! Get commutator long.
  /*! \return string commutator long */
  std::string const &		getCommutatorLong() const;
  //! Get optargc.
  /*! \return string optargc */
  std::string const &		getOptargc() const ;
  //! Get mandatory of option.
  /*! \return bool ismandatory */
  bool				getMandatory() const;
  //! Get values of option.
  /*! \return vector string with option values */
  std::vector<std::string> const & getValue() const;

 private:

  std::string			_name;
  std::string			_commutatorShort ;
  std::string			_commutatorLong;
  std::string			_optargc;
  bool				_mandatory;
  std::vector<std::string>	_values;
};

#endif // ! __OPTION_H__
