#include "JsonParser.h"
#include "JsonPrinter.h"
#include <iostream>
#include <fstream>

void printUsage() {
    std::cout << "JSON Parser & Generator\n";
    std::cout << "Usage:\n";
    std::cout << "  json-parser <command> [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  parse <file>           Parse and validate JSON file\n";
    std::cout << "  pretty <file>          Pretty print JSON file\n";
    std::cout << "  minify <file>          Minify JSON file\n";
    std::cout << "  validate <file>        Validate JSON syntax\n";
    std::cout << "  query <file> <key>     Query JSON value by key\n";
    std::cout << "\nExamples:\n";
    std::cout << "  json-parser parse data.json\n";
    std::cout << "  json-parser pretty data.json\n";
    std::cout << "  json-parser query data.json name\n";
}

void handleParse(const std::string& filename) {
    try {
        json::JsonValue value = json::JsonParser::parseFile(filename);
        std::cout << "✓ JSON is valid!\n";
        std::cout << "\nParsed structure:\n";
        std::cout << json::JsonPrinter::print(value, false) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "✗ Parse error: " << e.what() << "\n";
    }
}

void handlePretty(const std::string& filename) {
    try {
        json::JsonValue value = json::JsonParser::parseFile(filename);
        std::cout << json::JsonPrinter::print(value, true, 2) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << "\n";
    }
}

void handleMinify(const std::string& filename) {
    try {
        json::JsonValue value = json::JsonParser::parseFile(filename);
        std::cout << json::JsonPrinter::print(value, false) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << "\n";
    }
}

void handleValidate(const std::string& filename) {
    try {
        json::JsonParser::parseFile(filename);
        std::cout << "✓ JSON is valid!\n";
    } catch (const std::exception& e) {
        std::cerr << "✗ Invalid JSON: " << e.what() << "\n";
    }
}

void handleQuery(const std::string& filename, const std::string& key) {
    try {
        json::JsonValue value = json::JsonParser::parseFile(filename);
        
        if (value.isObject() && value.hasKey(key)) {
            std::cout << "Value for key '" << key << "':\n";
            std::cout << json::JsonPrinter::print(value[key], true, 2) << "\n";
        } else {
            std::cerr << "✗ Key '" << key << "' not found\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    
    std::string command = argv[1];
    
    if (command == "parse" && argc >= 3) {
        handleParse(argv[2]);
    } else if (command == "pretty" && argc >= 3) {
        handlePretty(argv[2]);
    } else if (command == "minify" && argc >= 3) {
        handleMinify(argv[2]);
    } else if (command == "validate" && argc >= 3) {
        handleValidate(argv[2]);
    } else if (command == "query" && argc >= 4) {
        handleQuery(argv[2], argv[3]);
    } else {
        printUsage();
        return 1;
    }
    
    return 0;
}