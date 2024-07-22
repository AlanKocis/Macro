#pragma once
#include "FileManager.h"
#include "Day.h"
#include "Entry.h"
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <iterator>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace app
{
	GLFWwindow *window;
	bool is_running = true;
	const int INIT_HEIGHT = 500, INIT_WIDTH = 400;
	std::string todays_date_global = "";
	FileManager& fileManager = FileManager::instance();

	std::vector<Day> days;
	
	void init()
	{
//		boilerplate
		glfwInit();

		window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "Macro Log", NULL, NULL);
		if (!window)
		{
			printf("Couldn't create GLFW window\n");
			glfwTerminate();
			exit(-1);
		}

		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "GLAD failed\n";
			exit(-1);
		}


		fileManager.init_buffers(days);

//		get user's local day as string
		time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm time_data = *std::localtime(&current_time);
		std::stringstream ss;
		ss << std::put_time(&time_data, "%m%d%Y");
		std::string todays_date;
		ss >> todays_date;
		todays_date_global = todays_date;


//		check end of buffer only to test if application has been opened today
		auto it = days.rbegin();
		if (!(it->date == todays_date))
		{
			days.emplace_back(Day(todays_date));
		}

//		init imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		printf("finished initializing.\n");
	}

	void update_gui()
	{
		int WIDTH = 0, HEIGHT = 0;
		glfwGetWindowSize(window, &WIDTH, &HEIGHT);
		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("1", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		static ImVec4 color(1, 0, 0, 1);
		ImGui::TextColored(color, "TEST\n\n");


		for (Day &day : days)
		{
			ImGui::TextColored(color, day.date.c_str());
			for (Entry &food : day.entries)
			{
				ImGui::Text("");






			}
		}
		ImGui::End();



		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2));
		ImGui::SetNextWindowPos(ImVec2(0, HEIGHT / 2));

		ImGui::Begin("2", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::Text(todays_date_global.c_str());



		static bool gate = false;
		if (ImGui::Button("Add Entry", ImVec2(90, 40)))		{gate = true; }

		if (gate)
		{
			ImGui::PushItemWidth(64);
			static char str[64];
			str[63] = '\0';
			ImGui::Text("test");	ImGui::SameLine();	ImGui::InputText("##label", str, IM_ARRAYSIZE(str));
			ImGui::PopItemWidth();

			ImGui::Text(str);

			if (ImGui::Button("Cancel", ImVec2(80, 30)))		{ gate = false; }
			
		}



		ImGui::End();
	}

	void run()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); 
		ImGui::NewFrame();


		update_gui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			is_running = false;
	}
}