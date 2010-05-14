#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include <iostream>
#include <string>
#include <map>
#include <boost/program_options.hpp>
#include <iostream>

//! SERVER:  Handle the command line when server is launched.

class Argument 
{
 public :

  //! Constructor.
  /*! \params command lines arguments */
  Argument(int, char** const &);
  //! Default destructor.
  virtual ~Argument();

  //! Get arguments from command line.
  /*! \return map of options command line  */
  boost::program_options::variables_map const & getArgument() const;

 private :

  //! Build boost commande line from command line arguments.
  /*! \params command lines arguments */
  int					BuildCommandLine(int argc, char** const & argv);

  boost::program_options::variables_map _args;
};

#endif
