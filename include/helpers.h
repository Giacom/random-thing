#ifndef HELPERS_H
#define HELPERS_H

#define MIN(VALUE, MIN) (VALUE > MIN ? MIN : VALUE)
#define MAX(VALUE, MAX) (VALUE < MAX ? MAX : VALUE)

#define CLAMP(VALUE, MIN, MAX) (VALUE > MIN ? (VALUE < MAX ? VALUE : MAX) : MIN)

#endif /* HELPERS_H */