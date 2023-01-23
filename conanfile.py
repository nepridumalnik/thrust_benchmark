from conans import ConanFile, CMake, tools
import os


class ThrustServer(ConanFile):
    name = 'Thrust'
    version = '1.0.0'

    settings = [
        'os',
        'build_type',
        'arch',
    ]

    options = {
        'shared': [True, False],
    }

    default_options = {
        'shared': True,
    }

    def configure(self):
        self.generators = [
            'cmake',
        ]

    def requirements(self):
        self.requires('thrust/1.17.0')

    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'

        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy('*.dll', dst='bin', src='bin', keep_path=False)
        self.copy('*.dylib', dst='lib', src='lib', keep_path=False)
