deb:
	config/autorun.sh
	sed -ie "s#^memcached \([^a-zA-Z]*\)clearwater\([^)]*\)#memcached \1+$$(echo ${VERSION}|sed -e 's#-#.#g')+\2#" debian/changelog
	sed -ie 's#^memcached #memcached-clearwater #' debian/changelog
	dpkg-buildpackage -rfakeroot -D -us -uc -i -I
	mv ../memcached-clearwater_*$$(echo ${VERSION}|sed -e 's#-#.#g')*.deb ${REPO_DIR}/binary
