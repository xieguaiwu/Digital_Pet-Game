Name:           DigitalPet
Version:        1.0.0
Release:        1%{?dist}
Summary:        A console-based virtual pet game

License:        MIT
URL:            https://github.com/xieguaiwu/Digital_Pet-Game
Source0:        %{url}/archive/v%{version}.tar.gz#/%{name}-%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  make
Requires:       glibc
Requires:       libstdc++

%description
Digital Pet is a personal C++ console-based virtual pet game.
Care for your pet — feed it, play with it, cook meals, and manage money.
Supports Windows and Linux. Started in May 2022.

%prep
%setup -q -n Digital_Pet-Game-%{version}

%build
make CXXFLAGS="%{optflags}"

%install
rm -rf %{buildroot}
install -Dm755 DigitalPet %{buildroot}%{_bindir}/DigitalPet
install -Dm644 LICENSE %{buildroot}%{_defaultlicensedir}/%{name}/LICENSE
install -Dm644 README.md %{buildroot}%{_defaultdocdir}/%{name}/README.md

%files
%license LICENSE
%doc README.md
%{_bindir}/DigitalPet

%changelog
* Sun Jun 07 2026 xieguaiwu <xieguaiwu@163.com> - 1.0.0-1
- Initial package for COPR
