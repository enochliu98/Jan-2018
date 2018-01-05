import javax.swing.*; 
import java.awt.*; 
public class Tower extends JPanel { 
int amountOfDisc = 3; 
Color color = Color.cyan; 
Disc[] disc; 
int maxDiscWidth, minDiscWidth, discHeight; 
char[] towerName; 
TowerPoint[] pointA, pointB, pointC; 
HandleMouse handleMouse; 
AutoMoveDisc autoMoveDisc; 
Tower(char[] towerName) { 
handleMouse = new HandleMouse(this); 
this.towerName = towerName; 
setLayout(null); 
setBackground(new Color(200, 226, 226)); 
} 
public void setAmountOfDisc(int number) { 
if (number <= 1) 
amountOfDisc = 1; 
else 
amountOfDisc = number; 
} 
public void setMaxDiscWidth(int m) { 
maxDiscWidth = m; 
} 
public void setMinDiscWidth(int m) { 
minDiscWidth = m; 
} 
public void setDiscHeight(int h) { 
discHeight = h; 
} 
public AutoMoveDisc getAutoMoveDisc() { 
return autoMoveDisc; 
} 
public void putDiscOnTower() { 
removeDisk(); 
int n = (maxDiscWidth - minDiscWidth) / amountOfDisc; 
disc = new Disc[amountOfDisc]; 
for (int i = 0; i < disc.length; i++) { 
disc[i] = new Disc(color); 
disc[i].setNumber(i); 
int diskwidth = minDiscWidth + i * n; 
disc[i].setSize(diskwidth, discHeight); 
disc[i].addMouseListener(handleMouse); 
disc[i].addMouseMotionListener(handleMouse); 
} 
pointA = new TowerPoint[amountOfDisc]; 
pointB = new TowerPoint[amountOfDisc]; 
pointC = new TowerPoint[amountOfDisc]; 
int vertialDistance = discHeight; 
for (int i = 0; i < pointA.length; i++) { 
pointA[i] = new TowerPoint(maxDiscWidth, 100 + vertialDistance); 
vertialDistance = vertialDistance + discHeight; 
} 
vertialDistance = discHeight; 
for (int i = 0; i < pointB.length; i++) { 
pointB[i] = new TowerPoint(2 * maxDiscWidth, 100 + vertialDistance); 
vertialDistance = vertialDistance + discHeight; 
} 
vertialDistance = discHeight; 
for (int i = 0; i < pointC.length; i++) { 
pointC[i] = new TowerPoint(3 * maxDiscWidth, 100 + vertialDistance); 
vertialDistance = vertialDistance + discHeight; 
} 
for (int i = 0; i < pointA.length; i++) { 
pointA[i].putDisc(disc[i], this); 
} 
handleMouse.setPointA(pointA); 
handleMouse.setPointB(pointB); 
handleMouse.setPointC(pointC); 
autoMoveDisc = new AutoMoveDisc(this); 
autoMoveDisc.setTowerName(towerName); 
autoMoveDisc.setAmountOfDisc(amountOfDisc); 
autoMoveDisc.setPointA(pointA); 
autoMoveDisc.setPointB(pointB); 
autoMoveDisc.setPointC(pointC); 
validate(); 
repaint(); 
} 
public void removeDisk() { 
if (pointA != null) { 
for (int i = 0; i < pointA.length; i++) { 
pointA[i].removeDisc(pointA[i].getDiscOnPoint(), this); 
pointB[i].removeDisc(pointB[i].getDiscOnPoint(), this); 
pointC[i].removeDisc(pointC[i].getDiscOnPoint(), this); 
} 
} 
} 
public void paintComponent(Graphics g) { 
super.paintComponent(g); 
int x1, y1, x2, y2; 
x1 = pointA[0].getX(); 
y1 = pointA[0].getY() - discHeight / 2; 
x2 = pointA[amountOfDisc - 1].getX(); 
y2 = pointA[amountOfDisc - 1].getY() + discHeight / 2; 
g.drawLine(x1, y1, x2, y2); 
x1 = pointB[0].getX(); 
y1 = pointB[0].getY() - discHeight / 2; 
x2 = pointB[amountOfDisc - 1].getX(); 
y2 = pointB[amountOfDisc - 1].getY() + discHeight / 2; 
g.drawLine(x1, y1, x2, y2); 
x1 = pointC[0].getX(); 
y1 = pointC[0].getY() - discHeight / 2; 
x2 = pointC[amountOfDisc - 1].getX(); 
y2 = pointC[amountOfDisc - 1].getY() + discHeight / 2; 
g.drawLine(x1, y1, x2, y2); 
g.setColor(Color.blue); 
x1 = pointA[amountOfDisc - 1].getX() - maxDiscWidth / 2; 
y1 = pointA[amountOfDisc - 1].getY() + discHeight / 2; 
x2 = pointC[amountOfDisc - 1].getX() + maxDiscWidth / 2; 
y2 = pointC[amountOfDisc - 1].getY() + discHeight / 2; 
int length = x2 - x1, height = 6; 
g.fillRect(x1, y1, length, height); 
int size = 5; 
for (int i = 0; i < pointA.length; i++) { 
g.fillOval(pointA[i].getX() - size / 2, 
pointA[i].getY() - size / 2, size, size); 
g.fillOval(pointB[i].getX() - size / 2, 
pointB[i].getY() - size / 2, size, size); 
g.fillOval(pointC[i].getX() - size / 2, 
pointC[i].getY() - size / 2, size, size); 
} g.drawString(towerName[0] + " ×ù", pointA[amountOfDisc - 1].getX(), 
pointA[amountOfDisc - 1].getY() + 50); g.drawString(towerName[1] + " ×ù", pointB[amountOfDisc - 1].getX(), 
pointB[amountOfDisc - 1].getY() + 50); g.drawString(towerName[2] + " ×ù", pointC[amountOfDisc - 1].getX(), pointC[amountOfDisc - 1].getY() + 50); 
} 
} 