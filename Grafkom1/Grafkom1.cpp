#include <glut.h>
#include <cmath> 

// Variabel untuk kontrol kamera
float camX = 0.0f, camY = 5.0f, camZ = 20.0f;
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;

// Fungsi untuk menggambar kubus sederhana (misal untuk rumah)
void drawCube(float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glutSolidCube(size);
}

// Fungsi untuk menggambar rumah
void drawHouse() {
    // Rumah dasar (berwarna abu-abu)
    glPushMatrix();
    glScalef(4.0f, 3.0f, 4.0f);
    glColor3f(0.5f, 0.7f, 1.0f);  // Warna biru muda
    drawCube(1.0f, 0.0f, 0.0f, 1.0f);  // Gambar kubus dengan warna abu-abu
    glPopMatrix();

    // Atap
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.8f, 0.2f, 0.2f);
    glutSolidCone(3.0f, 3.0f, 50, 50);
    glPopMatrix();

    // Pintu
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 2.0f);
    glScalef(0.8f, 1.5f, 0.1f);
    drawCube(1.0f, 0.3f, 0.15f, 0.05f);
    glPopMatrix();

    // Jendela Kiri
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 2.0f);
    glScalef(0.8f, 0.8f, 0.1f);
    drawCube(1.0f, 0.5f, 0.8f, 1.0f);
    glPopMatrix();

    // Jendela Kanan
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 2.0f);
    glScalef(0.8f, 0.8f, 0.1f);
    drawCube(1.0f, 0.5f, 0.8f, 1.0f);
    glPopMatrix();
}




// Fungsi tambahan untuk lantai
void drawRock(float x, float z) {
    glPushMatrix();
    glTranslatef(x, -1.4f, z);  // Posisi bebatuan di atas tanah
    glColor3f(0.5f, 0.5f, 0.5f); // Warna batu abu-abu
    glutSolidSphere(0.2f, 10, 10);  // Bebatuan berbentuk bola
    glPopMatrix();
}

void drawFloor() {
    // Tanah (warna hijau seperti rumput)
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);  // Hijau untuk rumput
    glTranslatef(0.0f, -1.5f, 0.0f);
    glScalef(20.0f, 0.1f, 20.0f);
    drawCube(1.0f, 0.0f, 0.5f, 0.0f);  // Tanah sebagai kubus besar
    glPopMatrix();

    // Bebatuan di atas tanah
    drawRock(2.0f, 3.0f);  // Bebatuan di koordinat (2, 3)
    drawRock(-3.0f, -5.0f);  // Bebatuan di koordinat (-3, -5)
    drawRock(5.0f, -4.0f);  // Bebatuan di koordinat (5, -4)
    drawRock(-7.0f, 2.0f);  // Bebatuan di koordinat (-7, 2)
    drawRock(4.0f, 7.0f);  // Bebatuan di koordinat (4, 7)
}



// Fungsi untuk menggambar pohon
void drawTree() {
    // Batang pohon
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f);
    glScalef(0.5f, 2.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Daun
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glColor3f(0.0f, 0.8f, 0.0f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

// Fungsi untuk menggambar bunga
void drawFlower() {
    // Batang bunga
    glPushMatrix();
    glColor3f(0.0f, 0.3f, 0.0f); // Warna hijau tua
    glScalef(0.1f, 1.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Daun kecil di batang
    glPushMatrix();
    glTranslatef(0.1f, 0.3f, 0.0f);
    glColor3f(0.0f, 0.8f, 0.0f);
    glutSolidSphere(0.15f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, 0.4f, 0.0f);
    glColor3f(0.0f, 0.8f, 0.0f);
    glutSolidSphere(0.15f, 20, 20);
    glPopMatrix();

    // Kelopak bunga (lingkaran kelopak)
    int petalCount = 6; // Jumlah kelopak
    float radius = 0.4f; // Radius kelopak dari pusat
    for (int i = 0; i < petalCount; i++) {
        float angle = i * (360.0f / petalCount) * 3.14159f / 180.0f;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glPushMatrix();
        glTranslatef(x, 0.9f, z); // Posisi kelopak
        glColor3f(1.0f, 0.4f, 0.7f); // Warna pink
        glutSolidSphere(0.2f, 20, 20); // Kelopak bunga
        glPopMatrix();
    }

    // Pusat bunga
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning untuk pusat bunga
    glutSolidSphere(0.2f, 20, 20);
    glPopMatrix();
}


// Fungsi untuk menggambar seluruh scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

    // Lantai
    glPushMatrix();
    drawFloor();
    glPopMatrix();

    // Rumah
    glPushMatrix();
    drawHouse();
    glPopMatrix();

    // Pohon dan bunga seperti sebelumnya
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 5.0f);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, -5.0f);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, -3.0f);
    drawFlower();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 3.0f);
    drawFlower();
    glPopMatrix();

    glutSwapBuffers();
}

// Fungsi untuk mengatur kamera dengan keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        camZ -= 1.0f;
        break;
    case 's':
        camZ += 1.0f;
        break;
    case 'a':
        camX -= 1.0f;
        break;
    case 'd':
        camX += 1.0f;
        break;
    case 'q':
        camY += 1.0f;
        break;
    case 'e':
        camY -= 1.0f;
        break;
    case 27: // Escape key
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Inisialisasi OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rumah dengan Pohon dan Bunga");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
