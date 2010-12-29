/*
 * Copyright (c) 2010, Mark Sands marksands07@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>

#include <boost/program_options.hpp>

#include "src/SearchableADT.hpp"
#include "src/Hash.hpp"
#include "src/Timer.hpp"

void ReadFile( SearchableADT<std::string>*& dictionary, std::string filename );
void Clear( SearchableADT<std::string>*& dictionary );
void CheckSpelling( SearchableADT<std::string>*& dictionary, std::string pattern );
void CheckReduce( SearchableADT<std::string>*& dictionary, std::string pattern );
void QuitProgram( SearchableADT<std::string>*& dictionary );

void SearchForWord( SearchableADT<std::string>*& dictionary, std::string word, int pos );
size_t CalculateShrinkability( SearchableADT<std::string>*& dictionary, std::string word, size_t length );

int main( int argc, char* argv[] )
{
  try {
    std::string filename;
    SearchableADT<std::string>* dictionary = new Hash<std::string>;

    boost::program_options::options_description generic("Options:");
    generic.add_options()
        ("h,help", "display this help and exit")
        ("f,file", boost::program_options::value<std::string>(&filename)->default_value("/usr/share/dict/words"), "load dictionary file")
        ("s,spellcheck", boost::program_options::value<std::vector<std::string> >(), "search for PATTERN in dictionary")
        ("r,reduce", boost::program_options::value<std::vector<std::string> >(), "display reducable words for PATTERN")
        ("v,version", "print version information and exit")
    ;

    boost::program_options::options_description visible("Allowed options");
    visible.add(generic);

    boost::program_options::options_description cmdline_options;
    cmdline_options.add(generic);

    boost::program_options::positional_options_description p;
    p.add("file", -1);

    boost::program_options::variables_map vm;
    store(boost::program_options::command_line_parser(argc, argv).
      options(cmdline_options).positional(p).run(), vm);
    notify(vm);

    if (vm.count("help")) {
      std::cout << visible << "\n";
      return 0;
    }

    if (vm.count("file")) {
      ReadFile( dictionary, filename );
    }

    if (vm.count("spellcheck")) {
      std::string temp;
      const std::vector<std::string> &s = vm["spellcheck"].as<std::vector<std::string> >();
      std::copy(s.begin(), s.end(), std::ostream_iterator<std::string>(cout, " "));
      //CheckSpelling( dictionary, s );
    }

    if (vm.count("reduce")) {
      std::string temp;
      const std::vector<std::string> &s = vm["reduce"].as<std::vector<std::string> >();
      std::copy(s.begin(), s.end(), std::ostream_iterator<std::string>(cout, " "));
      //CheckReduce( dictionary, temp );
    }

    if (vm.count("version")) {
        std::cout << "dictionary 1.0.0\n\n"
          << "Copyright 2010 Mark Sands.\n"
          << "This is free software; see the source for copying conditions. There is NO\n"
          << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
        return 0;
    }
  }
  catch( std::exception& e )
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}

void ReadFile( SearchableADT<std::string>*& dictionary, std::string filename )
{
  Timer t;

  if ( !dictionary->LoadFromFile(filename) )
    std::cerr << std::setw(3) << " " << "File failed to load!" << "\n";
}

void Clear( SearchableADT<std::string>*& dictionary )
{
  Timer t;

  dictionary->clear();
  std::cout << std::setw(3) << " " << "Dictionary cleared." << "\n";
}

void CheckSpelling( SearchableADT<std::string>*& dictionary, std::string pattern )
{
  Timer t;

  std::cout << "\n"
     << std::setw(3)  << " "
     << "Words found:" << "\n";

  SearchForWord( dictionary, pattern, 0 );

  std::cout << "\n";
}

void CheckReduce( SearchableADT<std::string>*& dictionary, std::string pattern )
{
  Timer t;

  std::cout << "\n";
  std::cout << "\n"
      << std::setw(3) << " "
      << "Shrinkability index: "
      << CalculateShrinkability( dictionary, pattern, pattern.length() - 1 )
      << "\n";

    std::cout << "\n";
}

void QuitProgram( SearchableADT<std::string>*& dictionary )
{
  delete dictionary;
}

void SearchForWord( SearchableADT<std::string>*& dictionary, std::string word, int pos )
{
  std::string temp = word;
  int qpos = -1;

  for ( size_t i = pos; i < temp.size(); i++ )
  {
    if ( temp[i] == '?' )
    {
      qpos = i;
      for ( int i = 0; i < 26; i++ )
      {
        temp[qpos] = i + 97;
        SearchForWord( dictionary, temp, qpos );

        if ( dictionary->isThere( temp ) ) {
          std::cout << setw(5) << " " << temp << "\n";
        }
      }
    }
  }
}

size_t CalculateShrinkability( SearchableADT<std::string>*& dictionary, std::string word, size_t length )
{
  try {
    std::string temp = word.substr( 0, length );
    if ( dictionary->isThere( temp ) ) {
      std::cout << std::setw(3) << " " << "\"" << word << "\" => \"" << temp << "\"\n";
      return CalculateShrinkability( dictionary, temp, temp.length() - 1 );
    }
  } catch( std::out_of_range &e ) {
    return word.length();
  }

  try {
    std::string temp = word.substr( 1, length );
    if ( dictionary->isThere( temp ) ) {
      std::cout << std::setw(3) << " " << "\"" << word << "\" => \"" << temp << "\"\n";
      return CalculateShrinkability( dictionary, temp, temp.length() - 1 );
    }
  } catch( std::out_of_range &e ) {
    return word.length();
  }

  std::cout << setw(3) << " " << "\"" << word << "\"\n";
  return word.length();
}