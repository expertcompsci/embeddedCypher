![Graph databases are cool](starFieldGraphDb.jpg)
# embeddedCypher
A portable, in-memory, persistant graph DBMS that implements the [openCypher](http://www.opencypher.org) query language.

### Hypothesis
As graph database systems are adopted more developers will feel comfortable using a graph query language. Much as SQL systems found adoption on small devices ([SQLite](http://sqlite.org) is the most installed DBMS in the world) devs could use graph databases on small devices with greater ability to represent and explore complex relationships using an easy to learn/use graph query language. An example openCypher query:

```MATCH (embeddedCypher)-[:implements]->(openCypher) RETURN *```

### Examples
For an example of a more capable device implementation, consider: Android via NDK where a KV store can treat SD storage as it would a disk or use faster Android "internal" memory efficiently as contiguous RAM. On the other end of the spectrum there exist processors available for around 1 USD that have C/C++ development tools available. The goal is ubiquitous:relaxed:deployment.

### How
While experimentation is encouraged now, an emphasis will be put on portability to the point of making embedding possible by abstracting byte order and solving performance issues etc. Unit and End To End testing will drive development.

Some major tools and components:
 * E2E and Unit testing: **CTest, Google GTest**
 * UnQLite: For the Key/Value backing store
 * Bisonc++: Parser
 * Flexc++: Lexical Scanner
 * Cmake/Clang/LLVM: A Reference build system

__Note__:
bisonc++ and flexc++ are programs used to generate the parser and lexical scanner respectively.  They generate the files identified below:

bisonc++:
  * parse.cc      
  * Parser.h - Not overwritten by bisonc++. Contains essential edits.
  * Parser.ih     
  * Parserbase.h

flexc++:
  * lex.cc
  * Scanner.h
  * Scanner.ih - Not overwritten by flexc++. Contains essential edits.
  * Scannerbase.h

The Bash script genParser.bash invokes bisonc++ and flexc++ for generation of the parser and scanner but is only needed if updates are made to the files parser/grammar.y and scanner/lexer.
