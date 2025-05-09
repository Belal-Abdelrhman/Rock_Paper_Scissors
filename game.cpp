string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Stone" , "Paper" , "Scissor" };
    return arrGameChoice[Choice - 1];
}
