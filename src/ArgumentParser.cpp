

#include "ArgumentParser.h"
#include "Logger.h"

#include <iostream>
#include <string>
#include <sstream>

CommandLineArgument::CommandLineArgument(
    const std::string shortName,
    const std::string longName
): mShortName(shortName), mLongName(longName) { }

std::string CommandLineArgument::GetShortName() const {
    return mShortName;
}
std::string CommandLineArgument::GetLongName() const {
    return mLongName;
}

void CommandLineArgument::SetData(const char *data) {
    mData = std::string(data);
}

std::string CommandLineArgument::GetData() const {
    return mData;
}

bool CommandLineArgument::MatchesArgumentName(const std::string &argument) const {

    if ((argument.size() > 2)
        && (argument.substr(0, 2) == "--")
        && (argument.substr(2, argument.size()) == GetLongName())) {

        return true;

    } else if((argument.size() > 1)
        && (argument.substr(0, 1) == "-")
        && (argument.substr(1, argument.size()) == GetShortName())) {

        return true;
    }

    return false;

}

ArgumentParser::ArgumentParser() { }

void ArgumentParser::AddArgument(
    const std::string &shortName,
    const std::string &longName) {

    mCommandLineArgumentList.push_back(CommandLineArgument(shortName, longName));

}

void ArgumentParser::ParseArguments(int argc, char **argv) {

    if((argc - 1) % 2 != 0) {

        std::stringstream ss;
        ss << "Uneven amount of arguments: " << argc << " in '";

        for(int i = 0; i < argc; i++) {
            ss << argv[i];

            if(i != (argc - 1)) {
                ss << " ";
            }
        }

        ss << "'";

        throw std::runtime_error(ss.str());
    }

    for(int i = 1; i < argc; i++) {

        const std::string argument = std::string(argv[i]);

        bool foundCommandLineArgument = false;

        for(auto &commandLineArgument : mCommandLineArgumentList) {

            if(commandLineArgument.MatchesArgumentName(argument)) {
                commandLineArgument.SetData(argv[i+1]);
                i++;
                foundCommandLineArgument = true;
                break;
            }
        }

        if(!foundCommandLineArgument) {
            LOG_ERROR("Unrecognized flag: %s", argv[i]);
            throw std::runtime_error("");
        }

    }

}

template<>
int ArgumentParser::GetValue<int>(const std::string &name) {

    for(const auto &commandLineArgument : mCommandLineArgumentList) {
        if(name == commandLineArgument.GetShortName() || name == commandLineArgument.GetLongName()) {

            if(commandLineArgument.GetData() == "") {
                return 0;
            }

            try {
                int value = std::stoi(commandLineArgument.GetData());

                return value;

            } catch(const std::exception &exception) {
                LOG_ERROR("Cannot convert %s to int", commandLineArgument.GetData().c_str());
                throw std::runtime_error("");
            }
        }
    }

    return 1;
}

template<>
std::string ArgumentParser::GetValue<std::string>(const std::string &name) {

    for(const auto &commandLineArgument : mCommandLineArgumentList) {

        if(name == commandLineArgument.GetShortName() || name == commandLineArgument.GetLongName()) {
            return std::string(commandLineArgument.GetData());
        }
    }

    return "";
}

template<>
float ArgumentParser::GetValue<float>(const std::string &name) {
    (void) name;

    return 1.0f;
}