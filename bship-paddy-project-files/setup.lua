-- Function to parse a line of the data file and return the barrier properties
local function parseLine(line)
    local xHalf, yHalf, zHalf, xOffset, yOffset, zOffset = string.match(line, "%(([^,]+), ([^,]+), ([^,]+), ([^,]+), ([^,]+), ([^,]+)%)")
    return tonumber(xHalf), tonumber(yHalf), tonumber(zHalf), tonumber(xOffset), tonumber(yOffset), tonumber(zOffset)
end

-- Function to add a barrier using the parsed data
local function addBarrierToGame(xHalf, yHalf, zHalf, xOffset, yOffset, zOffset)
    -- Assuming addBarrier is a C++ function exposed to Lua
    addBarrier(xHalf, yHalf, zHalf, xOffset, yOffset, zOffset)
end

-- Main execution
local function main()
    local filename = arg[1]  -- Command-line argument for the data file

    local file, err = io.open(filename, "r")
    if not file then
        error("Could not open file: " .. err)
    end

    for line in file:lines() do
        local xHalf, yHalf, zHalf, xOffset, yOffset, zOffset = parseLine(line)
        addBarrierToGame(xHalf, yHalf, zHalf, xOffset, yOffset, zOffset)
    end

    file:close()
end

-- Run the main function
main()
