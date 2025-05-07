#pragma once

#include <string>
#include <vector>

class CommandLineArgument {

public:

    CommandLineArgument(
        const std::string shortName,
        const std::string longName
    );

    std::string GetShortName() const;
    std::string GetLongName() const;

    void SetData(const char *data);
    std::string GetData() const;

    bool MatchesArgumentName(const std::string &name) const;

private:

    std::string mData = "";
    const std::string mShortName;
    const std::string mLongName;

};

class ArgumentParser {

public:

    ArgumentParser();

    /**
     * Add a named argument to the command line arg list
     *
     * @param shortName: Short flag name (ex. p -> "-p")
     * @param longName: Long flag name (ex. port -> "--port")
     */
    void AddArgument(
        const std::string &shortName,
        const std::string &longName
    );

    /**
     * Parse arguments straight from main
     *
     *  Skips program name and expects
     *  an even amount of named arguments
     */
    void ParseArguments(int argc, char **argv);

    /**
     * Get the value of a named argument
     *
     * Returns default values for:
     *      - std::string -> ""
     *      - int -> 0
     *      - float -> 0.0f
     */
    template <typename T>
    T GetValue(const std::string &name);

private:

    std::vector<CommandLineArgument> mCommandLineArgumentList;

};
