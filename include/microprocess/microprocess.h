#pragma once
#include <Windows.h>
#include <vector>
#include <string>

namespace microprocess
{
	class Microprocess;

	///Programm, compiled and loaded source
	class Program
	{
	friend Microprocess;
	private:
		char _hash[16];
		std::wstring _filename;
		HMODULE _library = NULL;
		void *_address = nullptr;
		size_t _refcount = 0;

	public:
		///Compiles program from source
		Program(const char *filename, char *error, size_t error_size)	noexcept;
		///Compiles program from source
		Program(const wchar_t *filename, char *error, size_t error_size)noexcept;
		///Returns if program is ok
		bool ok()														const noexcept;
		///Destroys program
		~Program()														noexcept;
	};

	///Microprocess, "bubble" executing `Program`
	class Microprocess
	{
	private:
		Program *_program	= nullptr;
		size_t _user_size	= 0;

		Microprocess()																noexcept;
		Microprocess(const Microprocess &other)										noexcept;

	public:
		///Microprocess hit cycle limit
		static const unsigned int time	= (unsigned int)-1;
		///Microprocess trued to access external memory
		static const unsigned int memory= (unsigned int)-2;

		///Returns total size required for microprocess
		static size_t total_size(size_t user_size)									noexcept;
		///Initializes memory as microprocess, can be called several times to change program or user space size
		bool init(Program *program, size_t user_size)								noexcept;
		///Finalizes microprocess
		void finalize()																noexcept;
		///Returns if microprocess is ok
		bool ok()																	const noexcept;
		///Returns user size
		size_t size()																const noexcept;
		///Returns total size
		size_t total_size()															const noexcept;
		///Returns pointer to user space
		void *user_space()															noexcept;
		///Returns constant pointer to user space
		const void *user_space()													const noexcept;
		///Executes microprocess for given cycle count
		unsigned int execute(unsigned int *cycles)									noexcept;
	};

	///Microprocess with fixed user space size
	template<size_t U> class FixedMicroprocess : public Microprocess
	{
	private:
		char _user_space[U];
		using Microprocess::init;

	public:
		///Creates uninitialized microprocess
		FixedMicroprocess()					noexcept;
		///Creates microprocess
		FixedMicroprocess(Program *program)	noexcept;
		///initializes microprocess
		bool init(Program *program)			noexcept;
		///Destroys microprocess
		~FixedMicroprocess()				noexcept;
	};
}

/*!
@mainpage Welcome to Microprocess (under construction)!
Microprocess is a secure "bubble", in which the code is executed with no influence on main program or other microprocesses. You want to make **millions of coroutines running quasi-parallel**? You are in the right library!

@section Features
Microprocesses use no virtual machines, no additional threads or processes, no interpreters and no system calls \- only fair C++ and little assembler. The main three features:
 - Microprocesses can't call insecure functions (otherwise the compilation will fail)
 - Microprocesses can't access memory beyond user space (otherwise they will be destroyed)
 - Microprocesses can't take control over the thread (otherwise they will be suspended)

@section Dependencies
The library depends on [Ironic Library](https://github.com/Meta-chan/ironic_liblary) and Visual Studio compiler.

@section Platforms
Currently Windows x86 only. In future will be extended to Linux, other architectures are questionable.

###### P.S. My code is not dirty, it is alternatively clean.
*/