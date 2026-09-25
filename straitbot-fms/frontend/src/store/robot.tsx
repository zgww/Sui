import { createContext, useContext, useState, useCallback, type ReactNode } from 'react'

interface RobotContextType {
  selectedRid: number | null
  setSelectedRid: (rid: number | null) => void
}

const RobotContext = createContext<RobotContextType>({
  selectedRid: null,
  setSelectedRid: () => {},
})

export function RobotProvider({ children }: { children: ReactNode }) {
  const [selectedRid, setSelectedRid] = useState<number | null>(null)
  return (
    <RobotContext.Provider value={{ selectedRid, setSelectedRid }}>
      {children}
    </RobotContext.Provider>
  )
}

export function useRobotId() {
  return useContext(RobotContext)
}
