
#ifndef GENE_H_
#define GENE_H_

#include <ostream>
using std::ostream;

class Gene {
    public:
        int value;
        bool isRobot;

        Gene();

        bool operator==(Gene other);

        friend ostream& operator<<(ostream& os, const Gene& gene);
};

#endif /* OPTIONS_H_ */
