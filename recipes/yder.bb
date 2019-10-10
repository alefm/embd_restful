DESCRIPTION = "Logging library for C applications"
HOMEPAGE = "https://github.com/babelouest/yder"
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://LICENSE;md5=40d2542b8c43a3ec2b7f5da31a697b88"

inherit cmake pkgconfig
SRC_URI = "git://github.com/babelouest/yder"
SRCREV = "${AUTOREV}"
S = "${WORKDIR}/git"

DEPENDS = "jansson orcania"
RDEPENDS_${PN} = "jansson orcania"
EXTRA_OECMAKE += "-DWITH_JOURNALD=off"