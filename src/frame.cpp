#include "config.h"
#include "efectos.h"
#include "graphics.h"
#include "main.h"

int frame2PixelLedMap[FRAME_BUFFER_SIZE] = { 
-1, -1, -1, -1, -1, -1, -1, 15, 12, 9, 6, 3, 0, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, -1, -1, -1, -1, -1,
-1, -1, -1, 87, 84, 81, 78, 75, 72, 69, 66, 63, 60, 57, 54, 51, 48, -1, -1, -1,
-1, -1, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132, 135, -1, -1,
-1, -1, 183, 180, 177, 174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 138, -1, -1,
-1, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216, 219, 222, 225, 228, 231, 234, 237, -1,
-1, 291, 288, 285, 282, 279, 276, 273, 270, 267, 264, 261, 258, 255, 252, 249, 246, 243, 240, -1,
294, 297, 300, 303, 306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351,
411, 408, 405, 402, 399, 396, 393, 390, 387, 384, 381, 378, 375, 372, 369, 366, 363, 360, 357, 354,
414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450, 453, 456, 459, 462, 465, 468, 471,
531, 528, 525, 522, 519, 516, 513, 510, 507, 504, 501, 498, 495, 492, 489, 486, 483, 480, 477, 474,
534, 537, 540, 543, 546, 549, 552, 555, 558, 561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591,
651, 648, 645, 642, 639, 636, 633, 630, 627, 624, 621, 618, 615, 612, 609, 606, 603, 600, 597, 594,
-1, 654, 657, 660, 663, 666, 669, 672, 675, 678, 681, 684, 687, 690, 693, 696, 699, 702, 705, -1,
-1, 759, 756, 753, 750, 747, 744, 741, 738, 735, 732, 729, 726, 723, 720, 717, 714, 711, 708, -1,
-1, -1, 762, 765, 768, 771, 774, 777, 780, 783, 786, 789, 792, 795, 798, 801, 804, 807, -1, -1,
-1, -1, 855, 852, 849, 846, 843, 840, 837, 834, 831, 828, 825, 822, 819, 816, 813, 810, -1, -1,
-1, -1, -1, 858, 861, 864, 867, 870, 873, 876, 879, 882, 885, 888, 891, 894, 897, -1, -1, -1,
-1, -1, -1, -1, -1, 927, 924, 921, 918, 915, 912, 909, 906, 903, 900, -1, -1, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, 930, 933, 936, 939, 942, 945, -1, -1, -1, -1, -1, -1, -1};


uint8_t lienzoHSV2[400][3] = {
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {239, 16, 252}, {232, 21, 251}, {233, 22, 251}, {233, 22, 251}, {232, 21, 251}, {231, 16, 251}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {246, 20, 251}, {241, 28, 250}, {237, 34, 249}, {233, 43, 248}, {234, 44, 248}, {231, 41, 244}, {231, 35, 244}, {227, 29, 243}, {226, 23, 243}, {227, 17, 248}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {3, 13, 253}, {249, 23, 251}, {245, 36, 249}, {243, 47, 248}, {241, 57, 246}, {238, 64, 245}, {234, 67, 241}, {231, 61, 236}, {228, 53, 232}, {225, 45, 231}, {224, 36, 233}, {221, 26, 237}, {220, 16, 243}, {221, 10, 248}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 15, 253}, {1, 27, 251}, {250, 43, 248}, {249, 54, 246}, {247, 68, 245}, {243, 83, 240}, {238, 94, 231}, {233, 97, 226}, {229, 90, 219}, {226, 78, 215}, {222, 63, 212}, {217, 48, 214}, {213, 34, 221}, {212, 24, 230}, {209, 16, 239}, {207, 8, 246}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {1, 23, 251}, {1, 38, 249}, {252, 57, 246}, {250, 76, 242}, {248, 93, 233}, {244, 111, 220}, {239, 130, 205}, {234, 139, 196}, {227, 133, 189}, {223, 117, 185}, {217, 89, 183}, {212, 65, 191}, {208, 49, 206}, {205, 34, 220}, {205, 25, 231}, {203, 14, 240}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {8, 21, 252}, {4, 35, 250}, {4, 52, 248}, {1, 73, 242}, {253, 99, 231}, {250, 122, 211}, {245, 153, 188}, {240, 188, 162}, {234, 215, 142}, {227, 204, 135}, {219, 184, 137}, {212, 133, 147}, {206, 93, 169}, {201, 68, 191}, {200, 47, 208}, {198, 34, 222}, {199, 20, 234}, {196, 13, 243}, {0, 0, 0},
  {0, 0, 0}, {9, 30, 252}, {9, 46, 250}, {6, 68, 245}, {5, 94, 232}, {2, 120, 212}, {254, 157, 178}, {249, 212, 137}, {244, 214, 114}, {236, 220, 96}, {226, 195, 85}, {211, 163, 81}, {199, 163, 103}, {198, 139, 146}, {192, 92, 174}, {191, 63, 197}, {190, 43, 215}, {190, 27, 229}, {189, 15, 241}, {0, 0, 0},
  {13, 19, 253}, {12, 34, 252}, {11, 54, 248}, {10, 82, 240}, {9, 111, 221}, {7, 152, 189}, {4, 216, 138}, {0, 208, 104}, {247, 206, 73}, {238, 191, 48}, {219, 161, 38}, {200, 159, 56}, {190, 154, 84}, {185, 167, 116}, {185, 120, 156}, {185, 75, 188}, {184, 49, 211}, {182, 31, 228}, {184, 19, 239}, {177, 11, 247},
  {17, 22, 253}, {16, 42, 252}, {17, 67, 244}, {16, 93, 233}, {14, 130, 209}, {13, 187, 163}, {10, 224, 116}, {5, 213, 74}, {251, 183, 32}, {0, 145, 7}, {201, 145, 7}, {182, 144, 30}, {176, 147, 64}, {174, 156, 101}, {176, 137, 148}, {174, 82, 185}, {174, 53, 211}, {175, 34, 227}, {176, 21, 237}, {173, 12, 246},
  {21, 24, 253}, {21, 44, 250}, {19, 68, 244}, {20, 98, 225}, {19, 139, 197}, {19, 215, 143}, {17, 214, 95}, {13, 178, 50}, {247, 170, 9}, {0, 0, 0}, {0, 0, 0}, {170, 141, 9}, {173, 135, 51}, {167, 145, 91}, {166, 155, 143}, {165, 94, 186}, {165, 60, 212}, {164, 40, 228}, {164, 25, 239}, {161, 15, 247},
  {23, 22, 252}, {23, 44, 249}, {24, 65, 239}, {24, 91, 222}, {25, 134, 191}, {27, 207, 135}, {25, 203, 89}, {28, 139, 44}, {42, 63, 8}, {0, 0, 0}, {0, 0, 0}, {161, 141, 9}, {159, 147, 50}, {158, 163, 89}, {154, 181, 138}, {157, 111, 192}, {157, 72, 217}, {156, 48, 232}, {157, 29, 241}, {155, 17, 248},
  {26, 21, 252}, {28, 38, 247}, {28, 59, 239}, {30, 85, 222}, {32, 120, 189}, {35, 181, 138}, {38, 179, 88}, {48, 139, 55}, {73, 90, 31}, {99, 109, 14}, {111, 156, 13}, {125, 225, 26}, {138, 229, 61}, {144, 213, 99}, {148, 160, 149}, {150, 109, 198}, {152, 77, 226}, {156, 48, 232}, {153, 30, 244}, {151, 18, 250},
  {31, 15, 252}, {33, 33, 247}, {34, 52, 240}, {37, 72, 222}, {38, 102, 195}, {43, 146, 153}, {52, 165, 108}, {61, 151, 86}, {73, 146, 66}, {89, 134, 53}, {100, 176, 52}, {114, 238, 61}, {126, 224, 75}, {135, 212, 108}, {140, 135, 166}, {144, 95, 205}, {146, 69, 230}, {153, 49, 236}, {148, 30, 249}, {148, 14, 252}, 
  {0, 0, 0}, {39, 25, 247}, {41, 41, 240}, {42, 59, 226}, {46, 85, 209}, {50, 113, 187}, {56, 153, 155}, {71, 156, 122}, {82, 145, 105}, {91, 168, 97}, {100, 204, 95}, {109, 209, 101}, {118, 210, 109}, {125, 149, 143}, {132, 104, 183}, {137, 79, 214}, {141, 59, 232}, {147, 48, 243}, {143, 26, 250}, {0, 0, 0},
  {0, 0, 0}, {42, 19, 249}, {43, 31, 244}, {47, 50, 237}, {52, 67, 227}, {56, 88, 214}, {61, 109, 196}, {67, 138, 175}, {76, 151, 155}, {87, 152, 142}, {97, 177, 139}, {105, 161, 150}, {113, 135, 168}, {120, 106, 186}, {126, 84, 202}, {131, 60, 222}, {136, 44, 237}, {138, 31, 245}, {140, 19, 251}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {44, 19, 247}, {48, 34, 241}, {53, 46, 234}, {56, 62, 224}, {63, 76, 213}, {68, 90, 203}, {76, 91, 195}, {86, 91, 189}, {96, 103, 187}, {102, 100, 191}, {109, 83, 199}, {116, 68, 207}, {121, 51, 217}, {128, 41, 226}, {133, 30, 238}, {138, 20, 247}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {46, 11, 249}, {50, 21, 245}, {55, 32, 239}, {56, 42, 233}, {61, 52, 225}, {65, 59, 218}, {73, 58, 212}, {80, 56, 209}, {92, 59, 207}, {99, 57, 209}, {107, 50, 214}, {114, 41, 221}, {120, 33, 227}, {127, 25, 233}, {131, 20, 242}, {134, 12, 249}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {49, 12, 249}, {55, 17, 245}, {58, 27, 239}, {62, 32, 234}, {66, 37, 229}, {72, 37, 226}, {80, 35, 223}, {89, 34, 222}, {96, 34, 223}, {106, 31, 226}, {113, 26, 230}, {120, 20, 236}, {130, 15, 243}, {136, 10, 249}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {56, 15, 246}, {62, 20, 242}, {68, 21, 239}, {70, 22, 236}, {78, 21, 233}, {85, 19, 233}, {93, 20, 234}, {100, 17, 237}, {109, 14, 240}, {119, 11, 244}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {63, 12, 246}, {67, 12, 244}, {77, 11, 243}, {85, 10, 243}, {92, 11, 243}, {97, 7, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

uint8_t lienzoHSV[400][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {239, 16, 252}, {232, 21, 251}, {233, 22, 251}, {233, 22, 251}, {232, 21, 251}, {231, 16, 251}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {246, 20, 251}, {241, 28, 250}, {237, 34, 249}, {233, 43, 248}, {234, 44, 248}, {231, 41, 244}, {231, 35, 244}, {227, 29, 243}, {226, 23, 243}, {227, 17, 248}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {3, 13, 253}, {249, 23, 251}, {245, 36, 249}, {243, 47, 248}, {241, 57, 246}, {238, 64, 245}, {234, 67, 241}, {231, 61, 236}, {228, 53, 232}, {225, 45, 231}, {224, 36, 233}, {221, 26, 237}, {220, 16, 243}, {221, 10, 248}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 15, 253}, {1, 27, 251}, {250, 43, 248}, {249, 54, 246}, {247, 68, 245}, {243, 83, 240}, {238, 94, 231}, {233, 97, 226}, {229, 90, 219}, {226, 78, 215}, {222, 63, 212}, {217, 48, 214}, {213, 34, 221}, {212, 24, 230}, {209, 16, 239}, {207, 8, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 23, 251}, {1, 38, 249}, {252, 57, 246}, {250, 76, 242}, {248, 93, 233}, {244, 111, 220}, {239, 130, 205}, {234, 139, 196}, {227, 133, 189}, {223, 117, 185}, {217, 89, 183}, {212, 65, 191}, {208, 49, 206}, {205, 34, 220}, {205, 25, 231}, {203, 14, 240}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {8, 21, 252}, {4, 35, 250}, {4, 52, 248}, {1, 73, 242}, {253, 99, 231}, {250, 122, 211}, {245, 153, 188}, {240, 188, 162}, {234, 215, 142}, {227, 204, 135}, {219, 184, 137}, {212, 133, 147}, {206, 93, 169}, {201, 68, 191}, {200, 47, 208}, {198, 34, 222}, {199, 20, 234}, {196, 13, 243}, {0, 0, 0}, {0, 0, 0}, {9, 30, 252}, {9, 46, 250}, {6, 68, 245}, {5, 94, 232}, {2, 120, 212}, {254, 157, 178}, {249, 212, 137}, {244, 214, 114}, {236, 220, 96}, {226, 195, 85}, {211, 163, 81}, {199, 163, 103}, {198, 139, 146}, {192, 92, 174}, {191, 63, 197}, {190, 43, 215}, {190, 27, 229}, {189, 15, 241}, {0, 0, 0}, {13, 19, 253}, {12, 34, 252}, {11, 54, 248}, {10, 82, 240}, {9, 111, 221}, {7, 152, 189}, {4, 216, 138}, {0, 208, 104}, {247, 206, 73}, {238, 191, 48}, {219, 161, 38}, {200, 159, 56}, {190, 154, 84}, {185, 167, 116}, {185, 120, 156}, {185, 75, 188}, {184, 49, 211}, {182, 31, 228}, {184, 19, 239}, {177, 11, 247}, {17, 22, 253}, {16, 42, 252}, {17, 67, 244}, {16, 93, 233}, {14, 130, 209}, {13, 187, 163}, {10, 224, 116}, {5, 213, 74}, {251, 183, 32}, {0, 145, 7}, {201, 145, 7}, {182, 144, 30}, {176, 147, 64}, {174, 156, 101}, {176, 137, 148}, {174, 82, 185}, {174, 53, 211}, {175, 34, 227}, {176, 21, 237}, {173, 12, 246}, {21, 24, 253}, {21, 44, 250}, {19, 68, 244}, {20, 98, 225}, {19, 139, 197}, {19, 215, 143}, {17, 214, 95}, {13, 178, 50}, {247, 170, 9}, {0, 0, 0}, {0, 0, 0}, {170, 141, 9}, {173, 135, 51}, {167, 145, 91}, {166, 155, 143}, {165, 94, 186}, {165, 60, 212}, {164, 40, 228}, {164, 25, 239}, {161, 15, 247}, {23, 22, 252}, {23, 44, 249}, {24, 65, 239}, {24, 91, 222}, {25, 134, 191}, {27, 207, 135}, {25, 203, 89}, {28, 139, 44}, {42, 63, 8}, {0, 0, 0}, {0, 0, 0}, {161, 141, 9}, {159, 147, 50}, {158, 163, 89}, {154, 181, 138}, {157, 111, 192}, {157, 72, 217}, {156, 48, 232}, {157, 29, 241}, {155, 17, 248}, {26, 21, 252}, {28, 38, 247}, {28, 59, 239}, {30, 85, 222}, {32, 120, 189}, {35, 181, 138}, {38, 179, 88}, {48, 139, 55}, {73, 90, 31}, {99, 109, 14}, {111, 156, 13}, {125, 225, 26}, {138, 229, 61}, {144, 213, 99}, {148, 160, 149}, {150, 109, 198}, {152, 77, 226}, {156, 48, 232}, {153, 30, 244}, {151, 18, 250}, {31, 15, 252}, {33, 33, 247}, {34, 52, 240}, {37, 72, 222}, {38, 102, 195}, {43, 146, 153}, {52, 165, 108}, {61, 151, 86}, {73, 146, 66}, {89, 134, 53}, {100, 176, 52}, {114, 238, 61}, {126, 224, 75}, {135, 212, 108}, {140, 135, 166}, {144, 95, 205}, {146, 69, 230}, {153, 49, 236}, {148, 30, 249}, {148, 14, 252}, {0, 0, 0}, {39, 25, 247}, {41, 41, 240}, {42, 59, 226}, {46, 85, 209}, {50, 113, 187}, {56, 153, 155}, {71, 156, 122}, {82, 145, 105}, {91, 168, 97}, {100, 204, 95}, {109, 209, 101}, {118, 210, 109}, {125, 149, 143}, {132, 104, 183}, {137, 79, 214}, {141, 59, 232}, {147, 48, 243}, {143, 26, 250}, {0, 0, 0}, {0, 0, 0}, {42, 19, 249}, {43, 31, 244}, {47, 50, 237}, {52, 67, 227}, {56, 88, 214}, {61, 109, 196}, {67, 138, 175}, {76, 151, 155}, {87, 152, 142}, {97, 177, 139}, {105, 161, 150}, {113, 135, 168}, {120, 106, 186}, {126, 84, 202}, {131, 60, 222}, {136, 44, 237}, {138, 31, 245}, {140, 19, 251}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {44, 19, 247}, {48, 34, 241}, {53, 46, 234}, {56, 62, 224}, {63, 76, 213}, {68, 90, 203}, {76, 91, 195}, {86, 91, 189}, {96, 103, 187}, {102, 100, 191}, {109, 83, 199}, {116, 68, 207}, {121, 51, 217}, {128, 41, 226}, {133, 30, 238}, {138, 20, 247}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {46, 11, 249}, {50, 21, 245}, {55, 32, 239}, {56, 42, 233}, {61, 52, 225}, {65, 59, 218}, {73, 58, 212}, {80, 56, 209}, {92, 59, 207}, {99, 57, 209}, {107, 50, 214}, {114, 41, 221}, {120, 33, 227}, {127, 25, 233}, {131, 20, 242}, {134, 12, 249}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {49, 12, 249}, {55, 17, 245}, {58, 27, 239}, {62, 32, 234}, {66, 37, 229}, {72, 37, 226}, {80, 35, 223}, {89, 34, 222}, {96, 34, 223}, {106, 31, 226}, {113, 26, 230}, {120, 20, 236}, {130, 15, 243}, {136, 10, 249}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {56, 15, 246}, {62, 20, 242}, {68, 21, 239}, {70, 22, 236}, {78, 21, 233}, {85, 19, 233}, {93, 20, 234}, {100, 17, 237}, {109, 14, 240}, {119, 11, 244}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {63, 12, 246}, {67, 12, 244}, {77, 11, 243}, {85, 10, 243}, {92, 11, 243}, {97, 7, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

uint8_t lienzoRGB[400][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {252, 236, 242}, {251, 230, 241}, {251, 229, 240}, {251, 229, 240}, {251, 230, 241}, {251, 235, 244}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {251, 231, 235}, {250, 222, 231}, {249, 215, 229}, {248, 206, 227}, {248, 205, 226}, {244, 204, 226}, {244, 210, 229}, {243, 215, 233}, {243, 221, 236}, {248, 231, 242}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {253, 241, 240}, {251, 228, 231}, {249, 213, 221}, {248, 202, 214}, {246, 191, 208}, {245, 183, 207}, {241, 177, 208}, {236, 179, 210}, {232, 183, 213}, {231, 190, 218}, {233, 200, 224}, {237, 212, 232}, {243, 227, 240}, {248, 238, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {253, 238, 238}, {251, 225, 224}, {248, 206, 210}, {246, 193, 200}, {245, 179, 191}, {240, 161, 183}, {231, 145, 178}, {226, 140, 183}, {219, 141, 187}, {215, 149, 193}, {212, 159, 200}, {214, 173, 209}, {221, 191, 220}, {230, 208, 230}, {238, 224, 239}, {245, 238, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {251, 229, 228}, {249, 212, 211}, {246, 191, 194}, {242, 169, 176}, {233, 148, 162}, {220, 124, 148}, {205, 100, 139}, {196, 89, 140}, {189, 90, 153}, {185, 100, 163}, {183, 119, 175}, {191, 142, 191}, {202, 166, 206}, {215, 190, 220}, {227, 208, 231}, {237, 226, 240}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {252, 235, 231}, {250, 219, 215}, {248, 202, 197}, {242, 174, 172}, {231, 141, 144}, {211, 110, 121}, {188, 75, 100}, {162, 42, 83}, {142, 22, 81}, {135, 27, 98}, {137, 38, 121}, {147, 70, 147}, {160, 107, 169}, {178, 140, 191}, {197, 169, 208}, {212, 192, 222}, {228, 215, 234}, {238, 230, 243}, {0, 0, 0}, {0, 0, 0}, {252, 229, 222}, {250, 214, 204}, {245, 189, 179}, {232, 157, 146}, {212, 119, 112}, {178, 68, 70}, {137, 23, 37}, {114, 18, 42}, {96, 13, 49}, {85, 20, 64}, {80, 29, 81}, {83, 37, 103}, {119, 66, 146}, {145, 111, 174}, {173, 148, 197}, {196, 178, 215}, {216, 204, 229}, {233, 226, 241}, {0, 0, 0}, {253, 240, 234}, {252, 228, 218}, {248, 209, 195}, {240, 182, 162}, {221, 145, 124}, {189, 97, 76}, {138, 34, 21}, {104, 20, 19}, {73, 14, 24}, {48, 12, 26}, {38, 14, 34}, {46, 21, 56}, {57, 33, 84}, {67, 40, 116}, {109, 82, 156}, {152, 132, 188}, {184, 170, 211}, {208, 200, 228}, {227, 221, 239}, {238, 236, 247}, {253, 240, 231}, {252, 226, 210}, {244, 205, 179}, {233, 180, 148}, {209, 138, 102}, {163, 82, 43}, {116, 40, 14}, {74, 20, 12}, {32, 9, 11}, {7, 3, 3}, {6, 3, 7}, {18, 13, 30}, {33, 27, 64}, {46, 39, 101}, {81, 68, 148}, {132, 125, 185}, {172, 167, 211}, {200, 196, 227}, {220, 217, 237}, {235, 234, 246}, {253, 241, 229}, {250, 228, 206}, {244, 208, 178}, {225, 180, 138}, {197, 139, 89}, {143, 78, 22}, {95, 47, 15}, {50, 26, 15}, {9, 3, 4}, {0, 0, 0}, {0, 0, 0}, {4, 4, 9}, {26, 24, 51}, {39, 42, 91}, {56, 64, 143}, {117, 124, 186}, {162, 167, 212}, {192, 197, 228}, {215, 218, 239}, {232, 235, 247}, {252, 242, 230}, {249, 230, 206}, {239, 213, 178}, {222, 189, 142}, {191, 151, 90}, {135, 95, 25}, {89, 61, 18}, {44, 36, 20}, {8, 8, 6}, {0, 0, 0}, {0, 0, 0}, {4, 5, 9}, {21, 28, 50}, {32, 48, 89}, {40, 75, 138}, {108, 133, 192}, {155, 173, 217}, {188, 202, 232}, {213, 221, 241}, {231, 237, 248}, {252, 244, 231}, {247, 235, 210}, {239, 221, 183}, {222, 201, 148}, {189, 169, 100}, {138, 122, 40}, {88, 82, 26}, {51, 55, 25}, {23, 31, 20}, {8, 14, 10}, {5, 13, 10}, {3, 26, 25}, {6, 47, 61}, {16, 66, 99}, {55, 103, 149}, {113, 153, 198}, {157, 186, 226}, {188, 202, 232}, {215, 226, 244}, {232, 240, 250}, {252, 248, 237}, {247, 240, 215}, {240, 231, 191}, {222, 214, 159}, {195, 188, 117}, {151, 153, 65}, {92, 108, 38}, {63, 86, 35}, {38, 66, 28}, {25, 53, 28}, {16, 52, 29}, {4, 61, 44}, {9, 75, 74}, {18, 92, 108}, {78, 139, 166}, {128, 175, 205}, {167, 202, 230}, {190, 208, 236}, {219, 234, 249}, {238, 245, 252}, {0, 0, 0}, {247, 245, 222}, {240, 239, 201}, {226, 226, 173}, {203, 209, 139}, {172, 187, 104}, {125, 155, 62}, {71, 122, 47}, {48, 105, 45}, {33, 97, 43}, {19, 95, 46}, {18, 101, 66}, {19, 109, 90}, {59, 143, 140}, {108, 174, 183}, {147, 198, 214}, {178, 214, 232}, {197, 221, 243}, {224, 240, 250}, {0, 0, 0}, {0, 0, 0}, {249, 249, 230}, {243, 244, 214}, {231, 237, 190}, {213, 227, 167}, {189, 214, 140}, {159, 196, 112}, {119, 175, 80}, {82, 155, 63}, {57, 142, 62}, {42, 139, 71}, {55, 150, 101}, {79, 168, 139}, {108, 186, 173}, {135, 202, 200}, {169, 217, 222}, {196, 228, 237}, {215, 237, 245}, {232, 245, 251}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {246, 247, 228}, {236, 241, 208}, {223, 234, 191}, {206, 224, 169}, {182, 213, 149}, {159, 203, 131}, {139, 195, 125}, {121, 189, 124}, {111, 187, 131}, {116, 191, 147}, {134, 199, 172}, {151, 207, 193}, {173, 217, 211}, {189, 225, 226}, {210, 234, 238}, {227, 242, 247}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {248, 249, 238}, {241, 245, 224}, {230, 239, 209}, {220, 233, 194}, {204, 225, 179}, {190, 218, 167}, {176, 212, 163}, {168, 209, 163}, {159, 207, 167}, {162, 209, 178}, {172, 214, 194}, {185, 221, 210}, {197, 227, 222}, {210, 233, 233}, {223, 240, 242}, {237, 247, 249}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 249, 237}, {240, 245, 228}, {229, 239, 213}, {220, 234, 204}, {210, 229, 195}, {203, 226, 193}, {195, 223, 192}, {192, 222, 195}, {193, 223, 201}, {198, 226, 212}, {206, 230, 222}, {217, 236, 233}, {228, 242, 243}, {239, 247, 249}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {241, 246, 231}, {233, 242, 223}, {227, 239, 219}, {222, 236, 215}, {216, 233, 213}, {215, 233, 215}, {215, 234, 219}, {221, 237, 227}, {226, 240, 234}, {233, 244, 242}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {240, 246, 234}, {237, 244, 232}, {234, 243, 232}, {233, 243, 233}, {232, 243, 234}, {239, 246, 241}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

uint8_t secEspiral[155][2] = {{9, 8}, {10, 8}, {10, 9}, {9, 9}, {8, 8}, {9, 7}, {10, 7}, {11, 8}, {11, 9}, {10, 10}, {9, 10}, {8, 10}, {7, 9}, {7, 8}, {7, 7}, {8, 6}, {9, 5}, {10, 5}, {11, 6}, {12, 7}, {12, 8}, {12, 9}, {12, 10}, {11, 11}, {10, 12}, {9, 12}, {8, 12}, {7, 11}, {6, 10}, {6, 9}, {6, 8}, {6, 7}, {6, 6}, {7, 5}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}, {14, 10}, {14, 11}, {13, 12}, {12, 13}, {11, 13}, {10, 14}, {9, 14}, {8, 14}, {7, 14}, {6, 13}, {5, 12}, {5, 11}, {4, 10}, {4, 9}, {4, 8}, {4, 7}, {5, 6}, {5, 5}, {6, 4}, {7, 3}, {8, 3}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 3}, {14, 3}, {15, 4}, {15, 5}, {15, 6}, {16, 7}, {16, 8}, {16, 9}, {16, 10}, {16, 11}, {15, 12}, {15, 13}, {14, 14}, {13, 15}, {12, 15}, {11, 16}, {10, 16}, {9, 16}, {8, 16}, {7, 16}, {6, 15}, {5, 14}, {4, 13}, {3, 12}, {3, 11}, {2, 10}, {2, 9}, {2, 8}, {2, 7}, {2, 6}, {3, 5}, {4, 4}, {5, 4}, {5, 3}, {6, 2}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 1}, {13, 2}, {14, 2}, {15, 3}, {16, 4}, {16, 5}, {17, 6}, {17, 7}, {17, 8}, {17, 9}, {17, 10}, {17, 11}, {16, 12}, {16, 13}, {15, 14}, {15, 15}, {14, 16}, {13, 17}, {12, 17}, {11, 18}, {10, 18}, {9, 18}, {8, 18}, {7, 18}, {6, 17}, {5, 16}, {4, 15}, {3, 14}, {2, 13}, {2, 12}, {2, 11}, {1, 10}, {1, 9}, {1, 8}, {1, 7}, {1, 6}, {1, 5}, {2, 4}, {3, 3}, {4, 2}, {5, 1}, {6, 1}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};

uint8_t secCuadrado[318][2] = {{9, 9}, {10, 9}, {10, 10}, {9, 10}, {8, 10}, {8, 9}, {8, 8}, {9, 8}, {10, 8}, {11, 8}, {11, 9}, {11, 10}, {11, 11}, {10, 11}, {9, 11},
  {8, 11}, {7, 11}, {7, 10}, {7, 9}, {7, 8}, {7, 7}, {8, 7}, {9, 7}, {10, 7}, {11, 7}, {12, 7}, {12, 8}, {12, 9}, {12, 10}, {12, 11},
  {12, 12}, {11, 12}, {10, 12}, {9, 12}, {8, 12}, {7, 12}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {6, 8}, {6, 7}, {6, 6}, {7, 6}, {8, 6},
  {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {13, 7}, {13, 8}, {13, 9}, {13, 10}, {13, 11}, {13, 12}, {13, 13}, {12, 13}, {11, 13},
  {10, 13}, {9, 13}, {8, 13}, {7, 13}, {6, 13}, {5, 13}, {5, 12}, {5, 11}, {5, 10}, {5, 9}, {6, 9}, {6, 8}, {5, 8}, {5, 7}, {5, 6}, {5, 5},
  {6, 5}, {7, 5}, {8, 5}, {9, 5}, {10, 5}, {11, 5}, {12, 5}, {13, 5}, {14, 5}, {14, 6}, {14, 7}, {14, 8}, {14, 9}, {14, 10}, {14, 11}, {14, 12},
  {14, 13}, {14, 14}, {13, 14}, {12, 14}, {11, 14}, {10, 14}, {9, 14}, {8, 14}, {7, 14}, {6, 14}, {5, 14}, {4, 14}, {4, 13}, {4, 12}, {4, 11},
  {4, 10}, {4, 9}, {4, 8}, {4, 7}, {4, 6}, {4, 5}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 4}, {11, 4}, {12, 4}, {13, 4}, {14, 4}, {15, 4},
  {15, 5}, {15, 6}, {15, 7}, {15, 8}, {15, 9}, {15, 10}, {15, 11}, {15, 12}, {15, 13}, {15, 14}, {15, 15}, {14, 15}, {13, 15}, {12, 15}, {11, 15},
  {10, 15}, {9, 15}, {8, 15}, {7, 15}, {6, 15}, {5, 15}, {4, 15}, {3, 15}, {3, 14}, {3, 13}, {3, 12}, {3, 11}, {3, 10}, {3, 9}, {3, 8}, {3, 7}, {3, 6},
  {3, 5}, {3, 4}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {16, 4}, {16, 5},
  {16, 6}, {16, 7}, {16, 8}, {16, 9}, {16, 10}, {16, 11}, {16, 12}, {16, 13}, {16, 14}, {16, 15}, {16, 16}, {15, 16}, {14, 16}, {13, 16}, {12, 16},
  {11, 16}, {10, 16}, {9, 16}, {8, 16}, {7, 16}, {6, 16}, {5, 16}, {4, 16}, {3, 16}, {2, 16}, {2, 15}, {2, 14}, {2, 13}, {2, 12}, {2, 11}, {2, 10},
  {2, 9}, {2, 8}, {2, 7}, {2, 6}, {2, 5}, {2, 4}, {2, 3}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 2}, {10, 2}, {11, 2}, {12, 2}, {13, 2},
  {14, 2}, {15, 2}, {16, 2}, {17, 3}, {17, 4}, {17, 5}, {17, 6}, {17, 7}, {17, 8}, {17, 9}, {17, 10}, {17, 11}, {17, 12}, {17, 13}, {17, 14},
  {17, 15}, {17, 16}, {16, 17}, {15, 17}, {14, 17}, {13, 17}, {12, 17}, {11, 17}, {10, 17}, {9, 17}, {8, 17}, {7, 17}, {6, 17}, {5, 17}, {4, 17},
  {3, 17}, {1, 14}, {1, 13}, {1, 12}, {1, 11}, {1, 10}, {1, 9}, {1, 8}, {1, 7}, {1, 6}, {1, 5}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1},
  {12, 1}, {13, 1}, {14, 1}, {18, 5}, {18, 6}, {18, 7}, {18, 8}, {18, 9}, {18, 10}, {18, 11}, {18, 12}, {18, 13}, {18, 14}, {14, 18}, {13, 18},
  {12, 18}, {11, 18}, {10, 18}, {9, 18}, {8, 18}, {7, 18}, {6, 18}, {5, 18}, {0, 12}, {0, 11}, {0, 10}, {0, 9}, {0, 8}, {0, 7}, {7, 0}, {8, 0}, {9, 0},
  {10, 0}, {11, 0}, {12, 0}, {19, 7}, {19, 8}, {19, 9}, {19, 10}, {19, 11}, {19, 12}, {12, 19}, {11, 19}, {10, 19}, {9, 19}, {8, 19}, {7, 19}
};