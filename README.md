New CCD Controller for LRS
===

Requirements
-----
- uuid / uuid-dev
- pThreads
- CFitsIO
- JsonCpp**
- RestBed**
- Spdlog**

** Provided by git submodules 

Build
-----

```
git clone --recursive git@gitlab.tng.iac.es:lrs/nCcdCtrl.git
mkdir nCcdCtrl/build
cd nCcdCtrl/build
cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ..
make 
```
# rest-json-cpp-boilerplate
