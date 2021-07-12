.. _changelog:


#########
Changelog
#########


******************
0.2.3 (unreleased)
******************


******************
0.2.2 (2021-07-12)
******************

Bug fixes
=========
- Fix unbound CD variable (:issue:`3` :merge:`4`). By `Kyle Brindley`_.

Internal Changes
================
- Update minimal Conda environment file (:pull:`48` :jira:`714`). By `Kyle Brindley`_.
- Migrate from ddw-bitcket.lanl.gov to re-git.lanl.gov (:issue:`1` :merge:`1`). By `Kyle Brindley`_.
- Update changelog issue and merge request link creation Sphinx directives (:issue:`2` :merge:`3`). By `Kyle Brindley`_.
- Use a commonly sourced environment activation script for CI/CD pipeline execution (:issue:`2` :merge:`3`). By `Kyle Brindley`_.
- Temporarily comment out Git tag push logic for master branch deploy until Gitlab permissions are resolved (:issue:`3`
  :merge:`4`). By `Kyle Brindley`_.
- Update Gitlab CI/CD job to allow Git tag pushes during production version deployment (:issue:`4` :merge:`6` :merge:`8`
  :merge:`10` :merge:`12`). By `Kyle Brindley`_.


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
