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
#include <cstdio>
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
			if (ImGui::TreeNode(day.date.c_str()))
			{
				for (Entry& food : day.entries)
				{

					ImGui::Text(food.get_name().c_str());
					static char foodStr[64];

				}
				ImGui::TreePop();
			}
		}
		ImGui::End();



		ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT / 2));
		ImGui::SetNextWindowPos(ImVec2(0, HEIGHT / 2));

		ImGui::Begin("2", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

		ImGui::Text(todays_date_global.c_str());



		static bool gate = false;

		if (!gate && ImGui::Button("Add Entry", ImVec2(90, 40)))		{gate = true; }

		if (gate)
		{
			ImGui::PushItemWidth(128);
			static char name_str[64] = "enter name\0";
			name_str[63] = '\0';
			ImGui::Text("Name:");		ImGui::SameLine();	ImGui::InputText("##NameInput", name_str, IM_ARRAYSIZE(name_str));
			for (int i = 0; i < 63; i++)
			{
				if (name_str[i] == ' ')
					name_str[i] = '_';
			}
			ImGui::PopItemWidth();
			
			ImGui::PushItemWidth(64);
			static float kcal = 0.0F;
			ImGui::Text("Kcal:");	ImGui::SameLine();	ImGui::InputFloat("##KcalInput", &kcal, 0.0F, 0.0F, "%.2f", 0);
			static float protein = 0.0F;
			ImGui::SameLine();	ImGui::Text("Protein:");
			ImGui::SameLine(); ImGui::InputFloat("##ProteinInput", &protein, 0.0F, 0.0F, "%.2f", 0);

			
//			TODO :: ADD ENTRY BUTTON 
			if (ImGui::Button("Add", ImVec2(80, 30)))
			{
				auto it = days.rbegin();
				//Entry food()
				//it->push_entry()
			}
			ImGui::SameLine();
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