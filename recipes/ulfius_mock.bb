DESCRIPTION = "Mock using ulfius web framework"
LICENSE 	= "CLOSED"
DEPENDS 	= "sqlite3 jansson ulfius yder orcania"

S = "${WORKDIR}/git"

PV = "1.0+git-${SRCPV}"
SRCREV  = "${AUTOREV}"

SRC_URI = "git://git@github.com:alefm/embd_restful.git;protocol=ssh"

inherit pkgconfig cmake

do_install() {
  install -d ${D}${bindir}
  install -m 0755 ulfius_mock ${D}${bindir}
}


DESCRIPTION = "Mock using ulfius web framework"
HOMEPAGE = "https://github.com/alefm/embd_restful"
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://LICENSE;md5=40d2542b8c43a3ec2b7f5da31a697b88"

inherit cmake pkgconfig
SRC_URI = "git://github.com/babelouest/ulfius"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

DEPENDS = "gnutls jansson libmicrohttpd"
RDEPENDS_${PN} = "gnutls jansson libmicrohttpd"
EXTRA_OECMAKE += "-DWITH_JOURNALD=off"
EXTRA_OECMAKE += "-DBUILD_ULFIUS_TESTING=off"
EXTRA_OECMAKE += "-DWITH_CURL=off"
