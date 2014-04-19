-- ����˹���飬��Ϸ�߼�����
-- qq_d_y
dofile("res/tetris/define.lua")

local state = g.MENU
local map = {}   -- [10][26]
local cur = { x = 0, y = 0, s = g.shape[1], }
local cursor_curpos = 1
local cursor_pos = 
{  
	{ 185, 200, }, { 185, 175, }, { 185, 150, },
}
local bgm = true
local score = 0			-- �÷�
local face = 0			-- ����
local over_ani = 26	-- ����ʱ����

function clean_map()
	for i = 1,10 do		-- 10 ��
		map[i] = {}
		for j = 1,26 do	-- 26 ��
			map[i][j] = 0	-- ����λ�ö�û�з���ռ��
		end
	end
end

function main_init()
	math.randomseed(os.time())
	clean_map()
	gen_shape()
	timer_reset()
	input_timer_reset()
	air.music_play("bgm")
	test()
end

function main_update()
	if state == g.GAME then
		if air.key_up("down") then
			g.update_interval = 0.2
		elseif air.key_down("down") then
			g.update_interval = 0.05
		elseif air.key_up("left") or air.key_up("right") or air.key_up("up") then
			g.key_flag = 1
		end
		local input_delay = 0
		if g.key_flag == 0 then
			input_delay = 0.15
		end
		if input_timer_pass() > input_delay then
			if air.key_down("left") then
				move_left()
				g.key_flag = 0
			elseif air.key_down("right") then
				move_right()
				g.key_flag = 0
			elseif air.key_down("up") then
				rotate_cur_shape()
				g.key_flag = 0
			end
			input_timer_reset()
		end
		if timer_pass() > g.update_interval then
			move_down_check()
			update_cur_shape()
			check_score(score)
			timer_reset()
		end
	elseif state == g.MENU then
		if g.key_flag == 1 then
			if input_timer_pass() < 0.3 then
				return
			end
		end
		if air.key_down("down") then
			cursor_curpos = cursor_curpos + 1
			if cursor_curpos == 4 then
				cursor_curpos = 3
			end
			g.key_flag = 1
			input_timer_reset()
		elseif air.key_up("down") then
			g.key_flag = 0
		end
		if air.key_down("up") then
			cursor_curpos = cursor_curpos - 1
			if cursor_curpos == 0 then
				cursor_curpos = 1
			end
			g.key_flag = 1
			input_timer_reset()
		elseif air.key_up("up") then
			g.key_flag = 0
		end
		if air.key_down("enter") then
			if cursor_curpos == 1 then
				state = g.GAME
				face = 1
			elseif cursor_curpos == 2 then
				if bgm then
					air.music_pause("bgm")
					bgm = false
				else
					air.music_play("bgm")
					bgm = true
				end
			elseif cursor_curpos == 3 then
				air.quit()
			end
			g.key_flag = 1
			input_timer_reset()
		elseif air.key_up("enter") then
			g.key_flag = 0
		end
	elseif state == g.OVER then
		if timer_pass() > g.update_interval then
			for i = 1, 10 do
				map[i][over_ani] = 1
			end
			over_ani = over_ani - 1
			if over_ani == 0 then
				state = g.MENU
				over_ani = 26
				face = 0
				score = 0
				clean_map()
			end
			timer_reset()
		end
	end
end

function main_draw()
	draw_map()
	draw_menu()
	draw_face()
end

-- ���Ƶ�ͼ
function draw_map()
	for i = 0, 10 do	-- 10 ��
		g.line(i * g.quad_size, 0, i * g.quad_size, 26 * g.quad_size, 0, 255, 0)
	end
	for i = 0, 26 do	-- 26 ��
		g.line(0, i * g.quad_size, 10 * g.quad_size, i * g.quad_size, 0, 255, 0)
	end
	for x = 1, 10 do
		for y = 1, 26 do
			if map[x][y] == 1 then
				g.quad(x, y, 0, 128, 0)
			end
		end
	end
	draw_cur_shape()
end

-- ���Ʋ˵�
function draw_menu()
	air.pen_print("1", 200, 200, 0, 255, 0, "start")
	if bgm then
		air.pen_print("1", 200, 175, 0, 255, 0, "music on")
	else
		air.pen_print("1", 200, 175, 0, 255, 0, "music off")
	end
	air.pen_print("1", 200, 150, 0, 255, 0, "quit")
	air.surface_draw_sprite("arrow", cursor_pos[cursor_curpos][1], cursor_pos[cursor_curpos][2])
	air.pen_print("2", 190, 16, 0, 255, 0, "score:"..score)
end

-- ���Ʊ���
function draw_face()
	if face == 0 then
		air.surface_draw_sprite("welcome", 180, 230)
	elseif face == 1 then
		air.surface_draw_sprite("normal", 180, 230)
	elseif face == 2 then
		air.surface_draw_sprite("over", 180, 230)
	end
end

-- ����һ����״
function gen_shape()
	local rnd = math.random(#g.prob)
	cur.x = 5
	cur.y = 26
	cur.s = g.shape[g.prob[rnd]]
end

-- ���µ�ǰ��״��λ��
function update_cur_shape()
		cur.y = cur.y - 1
end

-- ���Ƶ�ǰ��״
function draw_cur_shape()
	for i = 1, 8, 2 do
		g.quad(cur.x + cur.s[i], cur.y + cur.s[i + 1], cur.s[10], cur.s[11], cur.s[12])
	end
end

-- ��ת��ǰ��״
function rotate_cur_shape()
	local idx = cur.s[9]
	local t = { x = cur.x, y = cur.y, s = g.shape[idx], }
	for i = 1, 8, 2 do
		local check_x = t.x + t.s[i]
		local check_y = t.y + t.s[i + 1]
		if check_x < 1 or check_x > 10 then
			return
		end
		if check_y < 1 or check_y > 26 then
			return
		end
		if map[check_x][check_y] == 1 then
			return
		end
	end
	cur = t
end

-- ����Ƿ����ƶ������£���������
function move_down_check()
	-- ����Ƿ��Ѵ���
	for i = 1, 8, 2 do
		if cur.y + cur.s[i + 1] == 1 then
			handle_shape_stop()
		end
	end
	-- ��⽫Ҫ�ƶ�������һ���Ƿ����
	for i = 1, 8, 2 do
		local x = cur.x + cur.s[i]
		local y = cur.y + cur.s[i + 1]
		local check_y = y - 1
		if map[x][check_y] == 1 then
			handle_shape_stop()
		end
	end
end
function move_left()
	for i = 1, 8, 2 do
		local check_x = cur.x + cur.s[i] - 1
		local y = cur.y + cur.s[i + 1]
		if check_x < 1 or map[check_x][y] == 1 then
			return
		end
	end
	cur.x = cur.x - 1
end
function move_right()
	for i = 1, 8, 2 do
		local check_x = cur.x + cur.s[i] + 1
		local y = cur.y + cur.s[i + 1]
		if check_x > 10 or map[check_x][y] == 1 then
			return
		end
	end
	cur.x = cur.x + 1	
end

-- ִ�з��鴥���߼�
function handle_shape_stop()
	-- ����Ƿ��Ѵ���
	if cur.y == 26 then
		state = g.OVER
		face = 2
		return
	end
	-- ����ͼ
	for i = 1, 8, 2 do
		local x = cur.x + cur.s[i]
		local y = cur.y + cur.s[i + 1]
		map[x][y] = 1
	end
	check_full_line(cur.y)	-- ���м��
	gen_shape()				-- �����µķ���
end

-- ����Ƿ����С�����������ˣ������е����ݿ�������������һ�������ȥ���У�����һ�����������
function is_line_full(n)
	for i = 1, 10 do
		if map[i][n] == 0 then
			return false
		end
	end
	return true
end
function check_full_line(line)
	local full = false
	for cnt = 1, 4 do
		if is_line_full(line) then
			full = true
			score = score + 10
			for i = line, 25--[[26]] do
				for j = 1, 10 do
					map[j][i] = map[j][i + 1]
				end
			end
		else
			line = line + 1
		end
	end
	if full then
		air.music_play("line")
	end
end
function test()
	-- ����һ��ѭ����ģ�����д����ﵽ30�ε������debug��
	--[[for i = 1, 30 do
		for j = 1,10 do
			map[j][1] = 1
		end
		check_full_line(1)
	end]]
end
-- ��⵱ǰ���֣����ݻ��ָı���Ϸ�ٶ�
function check_score(s)
	if s > 100 then
		g.update_interval = 0.15
	elseif s > 200 then
		g.update_interval = 0.1
	elseif s > 300 then
		g.update_interval = 0.05
	end
end