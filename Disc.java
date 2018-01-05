import javax.swing.*; 
import java.awt.*; 
public class Disc extends JButton { 
int number; 
TowerPoint point; 
Color color; 
/* 
* Disc() { this.color=Color.cyan; setBackground(color); } 
*/ 
Disc(Color color) { 
this.color = color; 
setBackground(color); 
} 
public void setNumber(int n) { 
number = n; 
} 
public int getNumber() { 
return number; 
} 
public void setPoint(TowerPoint p) { 
point = p; 
} 
public TowerPoint getPoint() { 
return point; 
} 
}