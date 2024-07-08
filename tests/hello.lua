--print("Hello World!");
--print(name);


function printStr(str)
    print(str);
end


--local str;


function RepeatedlySpeak(str)

    for i=1, 100 do
        if i%2 == 0 then
            print(str);
        else
            print("Nothing To Say!");
        end
    end

end

function SpeakOnce(index)
    index = 1;
    repeat
        printStr("Again Nothing To Say!");
        index = index + 1;
    until index < 10
end


function main()
    RepeatedlySpeak("AnyWay");
    --SpeakOnce();
end


main();