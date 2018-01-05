import java.awt.*; 
import java.awt.event.*; 
import javax.swing.*; 
class SetDiscAcountDlg extends Dialog implements ActionListener 
{ 
JButton sure,cancel; 
Tower tower; 
JTextField text; 
SetDiscAcountDlg(JFrame f,Tower tower) 
{ super(f,"设置盘子数目 ",true); 
this.tower=tower; 
Box box1=Box.createVerticalBox(); sure=new JButton(" 确定 "); cancel=new JButton(" 退出 "); 
text=new JTextField(5); 
Box box2=Box.createHorizontalBox(); 
box2.add(sure); 
box2.add(cancel); box1.add(new JLabel(" 请输入 0-13 之间的数 ")); 
box1.add(text); 
box1.add(box2); 
add(box1); 
setBounds(100,100,210,100); 
sure.addActionListener(this); 
cancel.addActionListener(this); 
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
tower.amountOfDisc=Integer.valueOf(text.getText()); 
if(tower.amountOfDisc>0&&tower.amountOfDisc<13) 
{ 
tower.setAmountOfDisc(tower.amountOfDisc); 
tower.putDiscOnTower(); 
} 
else text.setText("请输入范围内的数字 "); 
} 
catch(NumberFormatException en) 
{ text.setText("请输入数字 (每个选项 )"); 
} 
} 
if(e.getSource()==cancel) 
{ 
setVisible(false); 
} 
} 
} 