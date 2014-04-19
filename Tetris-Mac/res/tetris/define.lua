-- ����˹���飬ȫ�ֱ����ͺ궨��
-- qq_d_y
g =
{
	-- ��Ϸ״̬
	MENU = 1,
	GAME = 2,
	OVER = 3,
	
	x_offset = 10,
	y_offset = 8,
	quad_size = 16,	-- ��ͼ��ߴ�
	
	update_interval = 0.2,	-- ���¼����������Ϸ�ٶ�
	
	-- �����߶�
	line = function(x1, y1, x2, y2, red, green, blue)
		air.surface_draw_line(g.x_offset + x1, g.y_offset + y1, g.x_offset + x2, g.y_offset + y2, red, green, blue, 1)
	end,
	-- ���Ʒ���
	quad = function(x, y, red, green, blue)
		if g.y_offset + ((y - 1) * g.quad_size) + 1 > g.y_offset + g.quad_size * 26 - 1 then
			return
		end
		-- +1��-1��Ϊ���ڷ���֮��������϶
		air.surface_draw_rect(g.x_offset + ((x - 1) * g.quad_size) + 1, g.y_offset + ((y - 1) * g.quad_size) + 1, g.quad_size - 1, g.quad_size - 1, red, green, blue, true) 
	end,
	
	-- ��״����	[1][2] 1st_xy_offset	[3][4] 2nd_xy_offset	[5][6] 3rd_xy_offset	[7][8] 4th_xy_offset	[9] rotate_to_shape	[10][11][12] rgb
	shape = 
	{
		[1] = { 0, 0, 1, 0, 0, 1, 1, 1, 1, 255, 0, 0, },	-- quad
		[2] = { 0, 0, 1, 0, 2, 0, 3, 0, 3, 0, 255, 0, },	-- line_x
		[3] = { 0, 0, 0, 1, 0, 2, 0, 3, 2, 0, 255, 0, },	-- line_y
		-- [4] .|.
		[4] = { 0, 0, 1, 0, 2, 0, 1, 1, 5, 255, 255, 0, },
		[5] = { 0, 0, 0, 1, 0, 2, 1, 1, 6, 255, 255, 0, },
		[6] = { 0, 1, 1, 1, 2, 1, 1, 0, 7, 255, 255, 0, },
		[7] = { 0, 1, 1, 0, 1, 1, 1, 2, 4, 255, 255, 0, },
		[8] = { 0, 2, 0, 1, 1, 1, 1, 0, 9, 0, 255, 255, },
		[9] = { 0, 0, 1, 0, 1, 1, 2, 1, 8, 0, 255, 255, },
		[10] = { 0, 0, 0, 1, 1, 1, 1, 2, 11, 0, 255, 255, },
		[11] = { 0, 1, 1, 1, 1, 0, 2, 0, 10, 0, 255, 255, },
	},
	-- ��״���ʱ�
	prob = { 1, 2, 4, 8, 10, },
	
	-- ����״̬
	key_flag = 0,   -- 0 ���£�1 ����
}

local tick = 0
function timer_pass()
	if tick == 0 then
		return tick
	end
	return os.clock() - tick
end
function timer_reset()
	tick = os.clock()
end

local input_timer_tick = 0
function input_timer_reset()
	input_timer_tick = os.clock()
end
function input_timer_pass()
	if input_timer_tick == 0 then
		return
	end
	return os.clock() - input_timer_tick
end