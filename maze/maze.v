module maze #( parameter maze_width = 6)(
input 		          clk,
input [maze_width - 1:0]  starting_col, starting_row, 	// indicii punctului de start
input  			  maze_in, 			// oferã informa?ii despre punctul de coordonate [row, col]
output reg [maze_width - 1:0] row, col,	 		// selecteazã un rând si o coloanã din labirint
output reg			  maze_oe,			// output enable (activeazã citirea din labirint la rândul ?i coloana date) - semnal sincron	
output reg		  maze_we, 			// write enable (activeazã scrierea în labirint la rândul ?i coloana date) - semnal sincron
output reg			  done);		 	// ie?irea din labirint a fost gasitã; semnalul rãmane activ 
`define start 0
`define dreapta 1
`define stanga 3
`define sus 2
`define jos 4
`define verificare 5


reg [5:0] state = 0, next_state;
reg [5:0] copie_coloana, copie_linie;
reg [1:0] dep;

always @(posedge clk) begin
   if (done == 0)
	    state <= next_state;
	end
	
	always @(*) begin
	 next_state = 0;
	 maze_we = 0;
	 maze_oe = 0;
	 done = 0;
	   case(state)
		  //start
		  `start: begin
			  row = starting_row;
			  col = starting_col;
			  copie_linie = row;
			  copie_coloana = col;
			  dep = 0;
			  maze_we = 1;
			  next_state = `dreapta;
			  end
			
			//dreapta
		   `dreapta: begin
		         copie_coloana = col;
				   col = col + 1;
					maze_oe = 1;
				   next_state = `verificare;
			  end
			//sus
			`sus: begin
			      copie_linie = row;
				   row = row - 1;
					maze_oe = 1;
					next_state = `verificare ;
				end
			//stanga
			`stanga:
			   begin
				   copie_coloana = col;
				   col = col - 1;
					maze_oe = 1;
			      next_state = `verificare;
				end
			//jos
			`jos:
			  begin
			     copie_linie = row;
			     row = row +1;
				  maze_oe = 1;
			     next_state = `verificare;
			  end
			  //verificare
			 `verificare: 
			  begin
			      // dep:
					// 0: dreapta
					// 1: jos
					// 2: stanga
					// 3: sus
						
			    case(dep)
				  
				  0: begin
				  
			      if (maze_in == 0) begin
				      //copie_linie = row;
						maze_we = 1;
						 if( row==0 || row == 63 || col == 0 || col ==63 )  done = 1;
						next_state = `jos;
						dep = 1;
					end
					else begin
						col = copie_coloana ;
						next_state = `sus;
						dep = 3;
					end
				  end
					1: begin
					 
					if (maze_in == 0) begin
					
				       //copie_coloana = col;
						 maze_we = 1;
						  if( row==0 || row == 63 || col == 0 || col ==63 )  done = 1;
						 next_state = `stanga;
						 dep = 2;
					end
					else begin
						 row = copie_linie ;
						 next_state = `dreapta;
						 dep = 0;
					end
				  end
				
					
					2: begin
					
					if (maze_in == 0) begin
					    //copie_linie = row;
						 maze_we = 1;
						  if( row==0 || row == 63 || col == 0 || col ==63 )  done = 1;
						 next_state = `sus;
						 dep = 3;
					end
					
					else begin
					     col = copie_coloana;
						  next_state = `jos;
						  dep = 1;
					end
				  end
						3: begin
					
					if (maze_in == 0) begin
					   //copie_coloana = col;
						maze_we = 1;
						 if( row==0 || row == 63 || col == 0 || col ==63 )  done = 1;
						next_state = `dreapta;
						dep = 0;
					end
					else begin
					   row = copie_linie;
						next_state = `stanga;
						dep = 2;
					end
				  end
				  

				  endcase
				  
				
					
					
			 end
						
				  
				     
			
	
	endcase
	end

				   
				
		     
		  
	


endmodule