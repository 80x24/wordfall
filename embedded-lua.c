#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int check_word(char *word)
{
	// --- NOTE --
	// I'm not doing any error handling here, so if there
	// is a problem, I am kind of fucked, but lua is nice,
	// so there really shouldn't be any issues.

	// create lua state and load lua libraries
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);

	// tell lua to run check-dict.lua
	luaL_dofile(L, "check-dict.lua");
	// push our check function to lua stack
	lua_getglobal(L, "check");
	// check to make sure that the top of the lua stack is a function
	lua_isfunction(L, -1);

	// push our word to the lua function
	lua_pushstring(L, word);
	// perform the function call
	lua_pcall(L, 1, 1, 0);
	/*if( != 0) {
		error(L, "error running function `f': %s", lua_tostring(L, -1));
	}*/

	// retrieve function result
	/*if(!lua_isnumber(L, -1)) {
		error(L, "function `check' must return a number");
	}*/

	// retrieve the result
	double result = lua_tonumber(L, -1);
	// pop retrieved value from Lua stack
	lua_pop(L, 1);

	// close lua state
	lua_close(L);

	if(result == 1) {
		return 1;
	}
	else if(result == 0) {
		return 0;
	}
	else {
		return 0;
	}
}