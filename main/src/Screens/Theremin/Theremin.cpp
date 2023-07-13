#include <algorithm>
#include "Theremin.h"
#include "Util/Services.h"
#include "Util/stdafx.h"


Theremin::Theremin() : audio(*(ChirpSystem*) Services.get(Service::Audio)), sem(xSemaphoreCreateBinary()),
					   timer(getToneDuration(sequence.getSize()), timerCB, sem),
					   audioThread([this](){ audioThreadFunc(); }, "Theremin audio", 2048, 5, 1){
	buildUI();
	sequence.refresh();

	xSemaphoreGive(sem);

	//debug
	lv_group_add_obj(inputGroup, sliderHorizontal);
	lv_group_add_obj(inputGroup, sliderVertical);

	lv_slider_set_value(sliderHorizontal, map(sequence.getBaseNoteIndex(), 0, ArpeggioSequence::MaxBaseNoteIndex, 0, SliderRange), LV_ANIM_OFF);
	lv_slider_set_value(sliderVertical, map(sequence.getSize(), 1, ArpeggioSequence::MaxSequenceSize, 0, SliderRange), LV_ANIM_OFF);

	lv_obj_add_event_cb(sliderHorizontal, [](lv_event_t* e){
		auto t = (Theremin*) e->user_data;
		auto mapped = map(lv_slider_get_value(e->target), 0, Theremin::SliderRange, 0, ArpeggioSequence::MaxBaseNoteIndex);
		t->sequence.setBaseNoteIndex(mapped);
	}, LV_EVENT_VALUE_CHANGED, this);

	lv_obj_add_event_cb(sliderVertical, [](lv_event_t* e){
		auto t = (Theremin*) e->user_data;
		auto mapped = map(lv_slider_get_value(e->target), 0, Theremin::SliderRange, 1, ArpeggioSequence::MaxSequenceSize);
		t->sequence.setSize(mapped);
		t->timer.setPeriod(getToneDuration(t->sequence.getSize()));
	}, LV_EVENT_VALUE_CHANGED, this);
}

void Theremin::setOrientation(float pitch, float roll){
	pitch = std::clamp(pitch, -AngleConstraint, AngleConstraint);
	roll = std::clamp(roll, -AngleConstraint, AngleConstraint);

	const auto horizontalX = (int16_t) (((roll + AngleConstraint) / (2 * AngleConstraint)) * SliderRange);
	const auto verticalY = (int16_t) (((pitch + AngleConstraint) / (2 * AngleConstraint)) * SliderRange);

	lv_slider_set_value(sliderVertical, verticalY, LV_ANIM_OFF);
	lv_slider_set_value(sliderHorizontal, horizontalX, LV_ANIM_OFF);
}

void Theremin::onStart(){
	audioThread.start();
	timer.start();
}

void Theremin::onStop(){
	timer.stop();
	audio.stop();
	audioThread.stop();
}

void IRAM_ATTR Theremin::timerCB(void* arg){
	BaseType_t priority = pdFALSE;
	xSemaphoreGiveFromISR(arg, &priority);
}

void Theremin::audioThreadFunc(){
	while(!xSemaphoreTake(sem, portMAX_DELAY));

	if(sequenceIndex == 0){
		sequence.refresh();
		timer.setPeriod(getToneDuration(sequence.getSize()));
	}

	if(sequenceIndex >= sequence.getSize()){
		sequenceIndex = 0;
		timer.setPeriod(PauseDuration);
		return;
	}

	const auto freq = sequence.getTones()[sequenceIndex];
	const uint16_t toneDuration = getToneDuration(sequence.getSize()) / 2;
	const Sound sound = { { freq, freq, toneDuration },
						  { 0,    0,    toneDuration } };

	audio.play(sound);

	sequenceIndex++;
}

constexpr uint32_t Theremin::getToneDuration(uint8_t sequenceSize){
	return SequenceDuration / sequenceSize;
}

void Theremin::buildUI(){
	lv_style_set_text_color(textStyle, lv_color_white());


	bg = lv_obj_create(*this);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 128, 128);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);
	lv_obj_set_style_bg_img_tiled(bg, true, 0);


	sliderHorizontal = lv_slider_create(bg);
	lv_obj_set_pos(sliderHorizontal, HorizontalBarX, HorizontalBarY);
	lv_obj_set_size(sliderHorizontal, SliderLength, SliderWidth);
	lv_obj_set_style_bg_img_src(sliderHorizontal, "S:/theremin/horizontalBar.bin", 0);
	lv_obj_set_style_bg_img_src(sliderHorizontal, "S:/theremin/dot.bin", LV_PART_KNOB);
	lv_obj_set_style_pad_hor(sliderHorizontal, 5, LV_PART_MAIN);
	lv_slider_set_range(sliderHorizontal, 0, SliderRange);


	sliderVertical = lv_slider_create(bg);
	lv_obj_set_pos(sliderVertical, VerticalBarX, VerticalBarY);
	lv_obj_set_size(sliderVertical, SliderWidth, SliderLength);
	lv_obj_set_style_bg_img_src(sliderVertical, "S:/theremin/verticalBar.bin", 0);
	lv_obj_set_style_bg_img_src(sliderVertical, "S:/theremin/dot.bin", LV_PART_KNOB);
	lv_obj_set_style_pad_ver(sliderVertical, 5, LV_PART_MAIN);
	lv_slider_set_range(sliderHorizontal, 0, SliderRange);


	textVertical = lv_obj_create(bg);
	lv_obj_set_layout(textVertical, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(textVertical, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(textVertical, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_size(textVertical, 60, 40);
	lv_obj_set_pos(textVertical, VerticalTextX, VerticalTextY);
	lv_obj_set_style_pad_column(textVertical, 3, 0);
	auto label = lv_label_create(textVertical);
	lv_label_set_text(label, "Move");
	lv_obj_add_style(label, textStyle, 0);
	auto arrow = lv_img_create(textVertical);
	lv_img_set_src(arrow, "S:/theremin/up.bin");
	lv_obj_set_style_pad_left(arrow, 1, 0);
	arrow = lv_img_create(textVertical);
	lv_img_set_src(arrow, "S:/theremin/down.bin");
	label = lv_label_create(textVertical);
	lv_label_set_text(label, "to change");
	lv_obj_add_style(label, textStyle, 0);
	label = lv_label_create(textVertical);
	lv_label_set_text(label, "the volume");
	lv_obj_add_style(label, textStyle, 0);


	textHorizontal = lv_obj_create(bg);
	lv_obj_set_layout(textHorizontal, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(textHorizontal, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(textHorizontal, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_size(textHorizontal, 80, 40);
	lv_obj_set_pos(textHorizontal, HorizontalTextX, HorizontalTextY);
	lv_obj_set_style_pad_column(textHorizontal, 3, 0);
	label = lv_label_create(textHorizontal);
	lv_label_set_text(label, "Move");
	lv_obj_add_style(label, textStyle, 0);
	arrow = lv_img_create(textHorizontal);
	lv_img_set_src(arrow, "S:/theremin/left.bin");
	lv_obj_set_style_pad_left(arrow, 1, 0);
	arrow = lv_img_create(textHorizontal);
	lv_img_set_src(arrow, "S:/theremin/right.bin");
	label = lv_label_create(textHorizontal);
	lv_label_set_text(label, "to change");
	lv_obj_add_style(label, textStyle, 0);
	label = lv_label_create(textHorizontal);
	lv_label_set_text(label, "the frequency");
	lv_obj_add_style(label, textStyle, 0);
}
