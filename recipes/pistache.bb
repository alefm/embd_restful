DESCRIPTION = "Pistache is a modern and elegant HTTP and REST framework for C++. It is entirely written in pure-C++11 and provides a clear and pleasant API."
HOMEPAGE = "https://github.com/oktal/pistache"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=fa818a259cbed7ce8bc2a22d35a464fc"

inherit cmake pkgconfig
SRC_URI = "git://github.com/oktal/pistache"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

# DEPENDS = "gnutls jansson libmicrohttpd"
# RDEPENDS_${PN} = "gnutls jansson libmicrohttpd"
EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"
EXTRA_OECMAKE += "-DPISTACHE_BUILD_DOCS=false"
EXTRA_OECMAKE += "-DPISTACHE_BUILD_TESTS=false"
EXTRA_OECMAKE += "-DPISTACHE_USE_SSL=false"
EXTRA_OECMAKE += "-DPISTACHE_BUILD_EXAMPLES=false"

do_configure_prepend () {
 git submodule update --init
}
