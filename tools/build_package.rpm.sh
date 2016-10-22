mkdir doc-pak
cp ../AUTHORS ../LICENSE ./doc-pak
cp ../README.md ./doc-pak/README
cp ../DESCRIPTION ./description-pak

checkinstall -y	--type=rpm \
		--install=no \
		--fstrans=yes \
		--pkgname=libwdc-dev \
		--pkgversion=$(git describe --abbrev=0 --tags | sed 's,^v,,') \
		--pkglicense=MIT \
		--pkgrelease=1 \
		--pkgsource="https://github.com/designerror/webdav-client-cpp" \
		--requires="$(cat ../REQUIREMENTS.UNIX.txt | sed ':a;N;$!ba;s/\n/,/g' | sed 's/(/\\(/g' | sed 's/)/\\)/g' | sed 's/>/\\>/g')" \
		--provides=wdc \
		--backup=no \
		--nodoc \
		--maintainer="designerror@ya.ru" \
		--pkggroup="wdc"

