import java.awt.*; 
import java.awt.event.*; 
import javax.swing.*; 
class SetDiscWidthDlg extends Dialog implements ActionListener 
{ 
Tower tower; 
JTextField maxtext,mintext,heighttext; 
JButton sure,cancel; 
GridLayout grid; 
SetDiscWidthDlg(JFrame f,Tower tower) 
{ super(f,"设置盘子大小 ",true); 
this.tower=tower; 
maxtext=new JTextField(5); 
mintext=new JTextField(5); 
heighttext=new JTextField(5); sure=new JButton(" 确定 "); cancel=new JButton(" 退出 "); 
sure.addActionListener(this); 
cancel.addActionListener(this); 
grid=new GridLayout(4,2); 
setLayout(grid); add(new JLabel(" 最大宽度 (像素 )"));add(maxtext); add(new JLabel(" 最小宽度 (像素 )"));add(mintext); add(new JLabel(" 盘子高度 (像素 )"));add(heighttext); 
add(sure);add(cancel); 
setBounds(100,100,200,200); 
addWindowListener(new WindowAdapter() 
{ 
public void windowClosing(WindowEvent e) 
{ 
setVisible(false); 
} 
}); 
setVisible(true); 
} 
public void actionPerformed(ActionEvent e) 
{ 
if(e.getSource()==sure) 
{ 
try 
{ 
tower.maxDiscWidth=Integer.valueOf(maxtext.getText()); 
tower.minDiscWidth=Integer.valueOf(mintext.getText()); 
tower.discHeight=Integer.valueOf(heighttext.getText()); 
tower.setMaxDiscWidth(tower.maxDiscWidth); 
tower.setMinDiscWidth(tower.minDiscWidth); 
tower.setDiscHeight(tower.discHeight); 
tower.putDiscOnTower(); 
validate(); 
} 
catch(NumberFormatException en) 
{ maxtext.setText("请输入数字 "); } 
} 
if(e.getSource()==cancel) 
{ 
setVisible(false); 
} 
} 
} 
