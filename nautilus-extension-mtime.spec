Summary:	Display mtime in ISO 8601 format
Name:		nautilus-extension-mtime
Version:	001
Release:	1%{?dist}
Group:		User Interface/Desktops
License:	GPLv2
Packager:	Andrew Clayton <andrew@digital-domain.net>
Url:		https://github.com/ac000/nautilus-extension-mtime
Source0:	nautilus-extension-mtime-%{version}.tar
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root

%description
A nautilus extension to add a column to the list view that displays the mtime
in ISO 8601 format. e.g 2013-03-13 20:23:35

%prep
%setup -q

%build
make

%install
rm -rf $RPM_BUILD_ROOT
install -Dp -m0755 nautilus-extension-mtime.so $RPM_BUILD_ROOT/usr/lib64/nautilus/extensions-3.0/nautilus-extension-mtime.so

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/usr/lib64/nautilus/extensions-3.0/nautilus-extension-mtime.so

%changelog
* Wed Mar 13 2013 Andrew Clayton <andrew@digital-domain.net> - 001-1
- Initial version
