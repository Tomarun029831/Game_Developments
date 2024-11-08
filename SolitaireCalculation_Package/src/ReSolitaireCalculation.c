#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//                                        turn_  1
//              .------_:=^=:_------_:=^=:_------_:=^=:_------_:=^=:_------.
// point:              |  1  |      |  2  |      |  3  |      |  4  |
//     lead:     .-----.      .-----.      .-----.      .-----.
// $ C_ K        |   2 | S_ A |   4 | D_ 2 |   6 | H_ 3 |   8 | C_ 4
//               '-----'      '-----'      '-----'      '-----'
//     stuck:

// ms (1~4):makestack stuckpoint
// dc (1~4):discard leadpoint
// ds (1~4) (1~4):disstuck stuckpoint leadpoint
// ud :undo
// ed :endgame

// ed
