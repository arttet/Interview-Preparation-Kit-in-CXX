from conan.tools.cmake import CMake, CMakeToolchain
from conans import ConanFile


class InterviewPreparationKitInCXXConan(ConanFile):
    name = "interview-preparation-kit-in-cxx"
    version = "0.0.1"

    # Optional metadata
    license = "MIT"
    author = "Artyom Tetyukhin"
    url = "https://github.com/arttet/Interview-Preparation-Kit-in-CXX"
    description = "The Interview Preparation Kit in C++"
    topics = ("cpp")

    # Binary configuration
    build_policy = "missing"
    generators = "CMakeDeps", "CMakeToolchain"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build_requirements(self):
        self.build_requires("gtest/1.11.0", force_host_context=True)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
