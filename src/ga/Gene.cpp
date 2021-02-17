#include "Gene.h"

// Default gene constructor
Gene::Gene() : value(0), isRobot(false) { }

bool Gene::operator==(Gene other) {
    return value == other.value && isRobot == other.isRobot;
}

ostream& operator<<(ostream& os, const Gene& gene) {
    if (gene.isRobot) {
        return os << "R" << gene.value;
    }
    return os << gene.value;
}
