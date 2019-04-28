package db1;
import java.sql.*;

public class db_join {

	public static void main(String[] args) throws SQLException {	
		Connection mydb = DriverManager.getConnection("jdbc:mysql://localhost:3306/jspbook?serverTimezone=UTC&allowPublicKeyRetrieval=true&useSSL=false","seleuchel","seleuchel");
		Statement mystmt = mydb.createStatement();
		ResultSet myrs = mystmt.executeQuery("SELECT * FROM STUDENT");
		
		Connection ordb = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:XE", "helios", "helios"); //ok-cmd에서 보는것 포트는 기본.
		Statement orstmt = ordb.createStatement();
		ResultSet orrs = orstmt.executeQuery("SELECT * FROM student");
		
		System.out.println("<<<<< MYSQL >>>>>");
		
		//columnName
		ResultSetMetaData met = myrs.getMetaData();
		int colCnt = met.getColumnCount();
        
        //print ColumnName
        for (int i = 1; i <= colCnt; i++)
            System.out.printf("%25s",met.getColumnName(i) + " "+ " | ");
        System.out.println("");
        
		while(myrs.next()) {
			System.out.printf("%25s",myrs.getString(1) + " | ");
			System.out.printf("%25s",myrs.getString(2) + " | ");
			System.out.printf("%25s",myrs.getString(3) + " | ");
			System.out.println("");
		}
		
		System.out.println("<<<<< ORACLE >>>>>");
		
		//columnName
		met = orrs.getMetaData();
		colCnt = met.getColumnCount();
        
        //print ColumnName
        for (int i = 1; i <= colCnt; i++)
            System.out.printf("%25s",met.getColumnName(i) + " "+ " | ");
        System.out.println("");
        
		while(orrs.next()) {
			System.out.printf("%25s",orrs.getInt(1) + " | ");
			System.out.printf("%25s",orrs.getString(2) + " | ");
			System.out.printf("%25s",orrs.getString(3) + " | ");
			System.out.println("");
		}
		
		myrs.close();
		orrs.close();
		mystmt.close();
		orstmt.close();
		
		//create table student2 in mysql
		Statement my_inst_stmt = mydb.createStatement();
		String strsql = "CREATE TABLE student2 (" + "SID INT, SNAME VARCHAR(25), GRADE INT );";
		my_inst_stmt.execute(strsql);
		
		//oracle student data
		Statement orstmt_mv = ordb.createStatement();
		ResultSet ormv = orstmt_mv.executeQuery("SELECT * FROM student");
		
		//insert oracle student -> mysql student2
		while(ormv.next()) {
			Statement tmpstmt = mydb.createStatement();
			String insertsql = "INSERT INTO student2 VALUES(" + 
					ormv.getInt(1) + "," +
					"\"" + ormv.getString(2) +"\"" + "," + 
					ormv.getInt(3) +
			");";//string comma! 
			tmpstmt.execute(insertsql);
		}
		
		//print student2
		Statement my_prt_stmt = mydb.createStatement();
		ResultSet my_prt_s2 = my_prt_stmt.executeQuery("SELECT * FROM student2");
		System.out.println("<<<<< copy >>>>>");
		
		//columnName
		met = my_prt_s2.getMetaData();
		colCnt = met.getColumnCount();
        
        //print ColumnName
        for (int i = 1; i <= colCnt; i++)
            System.out.printf("%25s",met.getColumnName(i) + " "+ " | ");
        System.out.println("");
        
		while(my_prt_s2.next()){
			System.out.printf("%25s",my_prt_s2.getString(1) + " | ");
			System.out.printf("%25s",my_prt_s2.getString(2) + " | ");
			System.out.printf("%25s",my_prt_s2.getString(3) + " | ");
			System.out.println("");
		}
		System.out.println("");
		
		//join
		Statement mysql_joinstmt = mydb.createStatement();
		ResultSet mysql_jointb = mysql_joinstmt.executeQuery("SELECT * FROM student join student2 on student.SID = student2.SID;");
		
		//print join ResultSet
		System.out.println("<<<<< Join student, student2 >>>>>");
		
		//columnName
		met = mysql_jointb.getMetaData();
		colCnt = met.getColumnCount();
        
        //print ColumnName
        for (int i = 1; i <= colCnt; i++)
            System.out.printf("%25s",met.getColumnName(i) + " "+ " | ");
        System.out.println("");
        
		while(mysql_jointb.next()) {
			System.out.printf("%25s",mysql_jointb.getString(1) + " | ");
			System.out.printf("%25s",mysql_jointb.getString(2) + " | ");
			System.out.printf("%25s",mysql_jointb.getString(3) + " | ");
			System.out.printf("%25s",mysql_jointb.getString(4) + " | ");
			System.out.printf("%25s",mysql_jointb.getString(5) + " | ");
			System.out.printf("%25s",mysql_jointb.getString(6) + " | ");
			System.out.println("");
		}

		
		ormv.close();
		my_prt_s2.close();
		
		mysql_jointb.close();
		orstmt_mv.close();
		my_inst_stmt.close();
		my_prt_stmt.close();
		mysql_joinstmt.close();
		mydb.close();
		ordb.close();
	}
}
