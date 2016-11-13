FROM        debian:jessie
MAINTAINER  gluttton@ukr.net
LABEL       Description="Container for building https://gitlab.com/Gluttton/munkres-cpp." Version="0.1"
RUN         sed 's/main/main contrib non-free/g' /etc/apt/sources.list \
         && apt-get update -qq \
         && apt-get install -y -qq \
                cmake \
                curl \
                g++ \
                gcovr \
                git \
                lcov \
                libarmadillo-dev \
                libboost-math-dev \
                libboost-system-dev \
                libeigen3-dev \
                libopencv-dev \
                qt5-default \
                libncurses5-dev \
         && for PACKAGE in manpages; \
            do \
                apt-get remove --purge --yes "${PACKAGE}"; \
            done \
         && apt-get autoremove --yes || true \
         && for FILE in $(find /var/log/ -type f); \
            do \
                : > ${FILE}; \
            done \
         && rm -rf /var/cache/man/* \
         && rm -rf /usr/share/doc/* \
         && rm -rf /usr/share/man/* \
         && rm -rf /usr/share/zoneinfo/* \
         && rm -rf /var/lib/apt/lists/* \
         && find . -name *~ -print0 | xargs -0 rm -f
