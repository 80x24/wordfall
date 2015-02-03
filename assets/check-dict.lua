--[[
This file is part of Word Fall.

Word Fall is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Word Fall is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Word Fall.  If not, see <http://www.gnu.org/licenses/>.
--]]

-- file existence is guaranteed upon startup

-- get lines from file
-- returns empty table if file doesn't exist
function get_lines(file)
	lines = {}
	local f = io.open(file, "r")
	for line in f:lines() do
		lines[#lines + 1] = line
	end
	f:close()
	return lines
end

-- check if the word is found in the dictionary.
function check_word(word)
	for i,j in pairs(lines) do
		if j == word then
			isWord = true
			break
		end
	end
	if isWord == true then
		return true
	else
		return false
	end
end

-- function to call from C
function check(word)
	local file = "assets/dict.txt"
	get_lines(file)
	if check_word(word) == true then
		return 1
	else
		return 0
	end
end