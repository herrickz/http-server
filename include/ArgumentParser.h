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

    void AddArgument(
        const std::string &shortName,
        const std::string &longName
    );

    void ParseArguments(int argc, char **argv);

    template <typename T>
    T getValue(const std::string &name);

private:

    std::vector<CommandLineArgument> mCommandLineArgumentList;

};
