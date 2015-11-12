deb:
	sed  -i~ 's/Source: memcached$$/Source: memcached-clearwater/; s/Package: memcached$$/Package: memcached-clearwater/; /Replaces: memcached/d; /Breaks: memcached/d' debian/control
	sed  -i~ '/Architecture: any/aReplaces: memcached' debian/control
	sed  -i~ '/Architecture: any/aBreaks: memcached' debian/control
	#
	cp -vp debian/memcached.install debian/memcached-clearwater.install
	cp -vp debian/memcached.postinst debian/memcached-clearwater.posinst
	cp -vp debian/memcached.postrm debian/memcached-clearwater.postrm
	#
	sed -i~ '#configure)#aln -s /etc/default/memcached-clearwater /etc/default/memcached' debian/memcached-clearwater.posinst
	sed -i~ '#configure)#aln -s /etc/init.d/memcached-clearwater /etc/init.d/memcached' debian/memcached-clearwater.posinst
	sed -i~ '#configure)#arm -f /etc/init.d/memcached /etc/default/memcached' debian/memcached-clearwater.posinst
	#
	rm -f scripts/memcached-clearwater-init 
	cp -vp scripts/memcached-init scripts/memcached-clearwater-init 
	#
	sed -i~ 's#debian/memcached.init#debian/$$(PACKAGE).init#g' debian/rules
	sed -i~ 's#debian/memcached$$#debian/$$(PACKAGE)#g' debian/rules
	sed -i~ 's/dh_auto_test/#dh_auto_test/' debian/rules
	sed -i~ 's#PACKAGE=memcached$$#PACKAGE=memcached-clearwater#g' debian/rules
	sed -i~ 's/#install -d $$(CURDIR)/install -d $$(CURDIR)/' debian/rules
	sed -i~ 's/#install -d $$(SCRIPTS)/install -d $$(SCRIPTS)/' debian/rules
	sed -i~ '#install -m 755 $$(CURDIR)/scripts/$$(PACKAGE)-init $$(CURDIR)/debian/$$(PACKAGE).init#d' debian/rules
	sed -i~ '/install -m 744 $$(CURDIR)\/scripts\/memcached-tool $$(SCRIPTS)#a\	install -m 755 $$(CURDIR)/scripts/$$(PACKAGE)-init $$(CURDIR)/debian/$$(PACKAGE).init' debian/rules
	#
	sed -i~ 's#my @exempted = qw(Makefile.am#my @exempted = qw(Makefile.cc Makefile.am#' t/whitespace.t
	sed -i~ '/find -L debian -type f -print0/d' t/whitespace.t
	sed -i~ '/my @exempted = qw(Makefile.cc Makefile.am/a    push(@exempted, split(/\\0/, `find -L debian -type f -print0`));' t/whitespace.t
	config/autorun.sh
	sed -i~ "s#^memcached \([^a-zA-Z]*\)clearwater\([^)]*\)#memcached \1+$$(echo ${VERSION}|sed -e 's#-#.#g')+\2#" debian/changelog
	sed -i~ 's#^memcached #memcached-clearwater #' debian/changelog
	dpkg-buildpackage -rfakeroot -D -us -uc -i -I
	mv ../memcached-clearwater_*$$(echo ${VERSION}|sed -e 's#-#.#g')*.deb ${REPO_DIR}/binary
