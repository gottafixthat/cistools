Summary: Cheetah IS Development Tools Name: cistools
Version: {VERSION}
Release: {RELEASE}
Copyright: 1998-2010, R. Marc Lewis, All Rights Reserved
Group: Development/Libraries
Source: cistools-{VERSION}.tgz
Buildroot: /var/tmp/cistools

%define _topdir /var/tmp/cistools
%define prefix /usr/lib

%description
The CIS Tools library contains various string manipulation
tools such as configuration file reading, string splitting, etc.
It also includes a MySQL abstraction class for C++.

%prep
%setup -q

%build
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
mkdir -p $RPM_BUILD_ROOT/usr/lib
mkdir -p $RPM_BUILD_ROOT/usr/include

install -m 644 libcistools.a   $RPM_BUILD_ROOT/usr/lib
install -m 755 libcistools.so  $RPM_BUILD_ROOT/usr/lib/libcistools.so.{VERSION}
ln -s libcistools.so.{VERSION}     $RPM_BUILD_ROOT/usr/lib/libcistools.so
install -m 644 ADB.h         $RPM_BUILD_ROOT/usr/include
install -m 644 CCValidate.h  $RPM_BUILD_ROOT/usr/include
install -m 644 Cfg.h         $RPM_BUILD_ROOT/usr/include
install -m 644 StrTools.h    $RPM_BUILD_ROOT/usr/include


%files
%defattr (-,root,root)
    
/usr/lib/libcistools.a
/usr/lib/libcistools.so
/usr/lib/libcistools.so.{VERSION}
/usr/include/ADB.h
/usr/include/CCValidate.h
/usr/include/Cfg.h
/usr/include/StrTools.h


