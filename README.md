
    nacltools-20101015
    Jay Sullivan
    Public Domain

This project, nacltools, provides commandline tools for the cryptographic operations provided by NaCl: Networking and Cryptography library ( see [http://nacl.cr.yp.to/](http://nacl.cr.yp.to/) ).  

------------------
 Installation 
------------------

First, download and build NaCl :

	cd
	wget http://hyperelliptic.org/nacl/nacl-20100830.tar.bz2
	bunzip2 < nacl-20100830.tar.bz2 | tar -xf -
	cd nacl-20100830
	./do

Then, install the NaCl headers to /usr/include/nacl and NaCl libraries to /usr/lib :

	cd build/`hostname -s`
	sudo mkdir /usr/include/nacl && sudo cp include/`bin/okabi`/* /usr/include/nacl
	sudo mkdir /usr/lib/nacl && sudo cp lib/`bin/okabi`/* /usr/lib
    
Finally, download and install nacltools ( installs to /usr/local/bin/ and man pages to /usr/share/man/man1/ ) :

	cd
	git clone git://github.com/notfed/nacltools.git
	cd nacltools
	make
	sudo make install

------------------
Documentation
------------------

See [http://nacltools.petio.org/](http://nacltools.petio.org/)
