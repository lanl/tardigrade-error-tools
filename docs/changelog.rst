.. _changelog:


#########
Changelog
#########


******************
0.2.1 (unreleased)
******************

Internal Changes
================
- Update minimal Conda environment file (:pull:`48` :jira:`714`). By `Kyle Brindley`_.


******************
0.2.1 (2021-06-24)
******************

New Features
============
- Auto bump micro/patch version for production release from master branch (:pull:`45` :jira:`695`). By `Kyle Brindley`_.

Bug fixes
=========
- Add CMake build type to CI/CD build scripts to correctly install the protected ``<project>Targets.cmake`` file
  (:pull:`35` :pull:`36`). By `Kyle Brindley`_.

Internal Changes
================
- Build version number from Git tags following the default ``setuptools_scm`` string style and using the predictive
  micro/patch update behavior for development versions (:pull:`44` :jira:`694`). By `Kyle Brindley`_.


******************
0.2.0 (2021-05-28)
******************

New Features
============
- Add deploy CMake files for build, deploy, discovery, and version comparisons (:jira:`623`, :pull:`31`). By `Kyle
  Brindley`_.
- Deploy the entire project (library, headers, cmake files) during CD scripts (:jira:`582`, :pull:`28`). By `Kyle
  Brindley`_.

Bug fixes
=========
- Only print the footer when the header is requested (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Fix the Doxygen/Sphinx dependence order (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Find the local system ``cmake3`` executable in CD scripts (:jira:`625`, :pull:`32`). By `Kyle Brindley`_.
- Remove version templating to help downstream project find the public headers (:jira:`633`, :pull:`33`). By `Kyle
  Brindley`_.

Internal Changes
================
- Consolidate error node print unit tests (:jira:`582`, :pull:`28`). By `Kyle Brindley`_.
- Remove the ``CXX`` compiler variable settings for build scripts (:jira:`665`,
  :pull:`34`. By `Kyle Brindley`_.


******************
0.1.0 (2020-11-30)
******************

Breaking changes
================

New Features
============

Bug fixes
=========

Documentation
=============

Internal Changes
================

Enhancements
============
