//6
//glDrawArrays(GL_TRIANGLES, 0, 6);

const float plain[] = {
    1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f

};                
//contains UVs
const float plain2[] = {
    1.0f, 0.0f, 1.0f,       0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
    1.0f, 0.0f, -1.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
    -1.0f, 0.0f, 1.0f,      0.0f, 1.0f, 0.0f,       0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,       0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f
};

//backup
/*
const float plain2[] = {
1.0f, 0.0f, 1.0f,       0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
1.0f, 0.0f, -1.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
-1.0f, 0.0f, -1.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f,
-1.0f, 0.0f, 1.0f,      0.0f, 1.0f, 0.0f,       0.0f, 1.0f,
1.0f, 0.0f, 1.0f,       0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
-1.0f, 0.0f, -1.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f
};
*/