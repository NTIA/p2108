#include "CommaSeparatedIterator.h"

#include <cstddef>   // for std::ptrdiff_t
#include <iterator>  // for std::input_iterator_tag,

CommaSeparatedIterator::CommaSeparatedIterator(std::istream &stream):
    stream_(stream) {
    ++(*this);  // Move to the first line
}

/***********************************************************************
 * Pre-increment operator.
 * 
 * Advances the iterator to the next line and splits it into two substrings.
 * If the end of the stream is reached, both substrings will be empty. Both
 * parsed substrings are converted to lowercase.
 * 
 * @return A reference to the updated iterator.
 **********************************************************************/
CommaSeparatedIterator &CommaSeparatedIterator::operator++() {
    if (std::getline(stream_, line_)) {
        size_t pos = line_.find(',');
        if (pos != std::string::npos) {
            first_ = line_.substr(0, pos);
            second_ = line_.substr(pos + 1);
        } else {
            first_ = line_;
            second_ = "";
        }
        // Convert both substrings to lowercase
        std::transform(
            first_.begin(),
            first_.end(),
            first_.begin(),
            [](const char c) { return static_cast<char>(std::tolower(c)); }
        );
        std::transform(
            second_.begin(),
            second_.end(),
            second_.begin(),
            [](const char c) { return static_cast<char>(std::tolower(c)); }
        );
    } else {
        first_ = second_ = "";  // End of stream
    }
    return *this;
}

/***********************************************************************
 * Dereference operator.
 * 
 * Returns the current pair of substrings (first and second).
 * 
 * @return A pair containing the two substrings from the current line.
 **********************************************************************/
CommaSeparatedIterator::value_type CommaSeparatedIterator::operator*() const {
    return {first_, second_};
}

/***********************************************************************
 * Conversion to boolean.
 * 
 * Checks if the iterator is still valid (not at the end of the input).
 * 
 * @return True if there are still lines to read, otherwise false.
 **********************************************************************/
CommaSeparatedIterator::operator bool() const {
    return !line_.empty();
}