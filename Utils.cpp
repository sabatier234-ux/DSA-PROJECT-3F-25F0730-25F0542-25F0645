#include "Common.h"

int splitLine(const string& line, char delimiter, string parts[], int maxParts) {
    int count = 0;
    string current = "";
    for (unsigned i = 0; i < line.size(); i++) {
        if (line[i] == delimiter) {
            if (count < maxParts) parts[count++] = current;
            current = "";
        } else if (line[i] != '\r') {
            current += line[i];
        }
    }
    if (count < maxParts) parts[count++] = current;
    return count;
}

int toInt(const string& text) {
    if (text.size() == 0 || text.size() > 9) return -1;
    int value = 0;
    for (unsigned i = 0; i < text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') return -1;
        value = value * 10 + (text[i] - '0');
    }
    return value;
}

string intToString(int value) {
    if (value == 0) return "0";
    bool negative = value < 0;
    if (negative) value = -value;
    string result = "";
    while (value > 0) {
        result = char('0' + value % 10) + result;
        value /= 10;
    }
    return negative ? "-" + result : result;
}

string trimText(const string& text) {
    int start = 0;
    int end = (int)text.size() - 1;
    while (start <= end && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r' || text[start] == '\n')) start++;
    while (end >= start && (text[end] == ' ' || text[end] == '\t' || text[end] == '\r' || text[end] == '\n')) end--;
    return text.substr(start, end - start + 1);
}

string twoDigits(int value) {
    if (value < 10) return "0" + intToString(value);
    return intToString(value);
}

string padRight(const string& text, int width) {
    string result = text;
    while ((int)result.size() < width) result += ' ';
    return result;
}
