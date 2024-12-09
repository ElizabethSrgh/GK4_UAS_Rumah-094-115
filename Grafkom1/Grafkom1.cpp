#include <glut.h>
#include <cmath>

// Variabel untuk kontrol kamera
float camX = 0.0f, camY = 5.0f, camZ = 20.0f; // Posisi awal kamera
float angleH = 0.0f;  // Sudut horizontal
float angleV = 0.0f;  // Sudut vertikal
float radius = 20.0f; // Jarak kamera dari pusat scene

// Fungsi untuk menggambar kubus sederhana
void drawCube(float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glutSolidCube(size);
}

// Fungsi untuk menggambar rumah
void drawHouse() {
    // Rumah dasar
    glPushMatrix();
    glScalef(4.0f, 3.0f, 4.0f);
    drawCube(1.0f, 0.5f, 0.7f, 1.0f); // Warna rumah
    glPopMatrix();

    // Atap
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.8f, 0.2f, 0.2f); // Warna atap
    glutSolidCone(3.0f, 3.0f, 50, 50);
    glPopMatrix();

    // Pintu
    glPushMatrix();
    glTranslatef(0.0f, -0.6f, 2.0f);
    glScalef(0.8f, 1.8f, 0.1f);
    drawCube(1.0f, 0.3f, 0.15f, 0.05f); // Warna pintu
    glPopMatrix();

    // Gagang pintu
    glPushMatrix();
    glTranslatef(0.3f, -0.8f, 2.05f);
    glColor3f(0.8f, 0.8f, 0.0f); // Warna gagang pintu (emas)
    glutSolidSphere(0.1f, 20, 20); // Bentuk gagang pintu
    glPopMatrix();

    // Jendela kiri
    glPushMatrix();
    glTranslatef(-1.2f, 0.0f, 2.05f);
    glScalef(1.0f, 1.0f, 0.1f);
    drawCube(1.0f, 0.6f, 0.8f, 1.0f); // Warna jendela (kaca)
    glPopMatrix();

    // Jendela kanan
    glPushMatrix();
    glTranslatef(1.2f, 0.0f, 2.05f); // Posisi jendela kanan
    glScalef(1.0f, 1.0f, 0.1f);
    drawCube(1.0f, 0.6f, 0.8f, 1.0f); // Warna jendela (kaca)
    glPopMatrix();
}

// Fungsi untuk menggambar lantai
void drawFloor() {
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f);  // Warna hijau seperti rumput
    glTranslatef(0.0f, -1.5f, 0.0f);
    glScalef(20.0f, 0.1f, 20.0f);
    drawCube(1.0f, 0.0f, 0.5f, 0.0f);
    glPopMatrix();
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

// Fungsi untuk menggambar pohon dengan lantai sebagai dasar
void drawTreeWithBase() {
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    drawTree();
    glPopMatrix();
}

// Fungsi untuk menggambar seluruh scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Hitung posisi kamera dengan spherical coordinates
    camX = radius * cos(angleV) * sin(angleH);
    camY = radius * sin(angleV);
    camZ = radius * cos(angleV) * cos(angleH);

    // Kamera
    gluLookAt(camX, camY, camZ,   // Posisi kamera
        0.0f, 0.0f, 0.0f,   // Titik yang dituju (pusat scene)
        0.0f, 1.0f, 0.0f);  // Arah atas

    // Lantai
    drawFloor();

    // Rumah
    drawHouse();

    // Pohon
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 5.0f);
    drawTreeWithBase(); // Gunakan pohon dengan dasar lantai
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, -5.0f);
    drawTreeWithBase(); // Gunakan pohon dengan dasar lantai
    glPopMatrix();

    glutSwapBuffers();
}

// Fungsi untuk kontrol kamera dengan keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // Naikkan sudut vertikal
        angleV += 0.05f; // Tidak ada batas
        break;
    case 's': // Turunkan sudut vertikal
        angleV -= 0.05f; // Tidak ada batas
        break;
    case 'a': // Geser sudut horizontal ke kiri
        angleH -= 0.05f;
        break;
    case 'd': // Geser sudut horizontal ke kanan
        angleH += 0.05f;
        break;
    case 'q': // Perbesar radius (menjauh)
        radius += 1.0f;
        break;
    case 'e': // Perkecil radius (mendekat)
        if (radius > 5.0f) radius -= 1.0f; // Batas radius minimum
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
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("UAS Lab. GrafKom | Elizabeth [094] & Mutiara [115]");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}